#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  temp ;
typedef  int off_t ;

/* Variables and functions */
 int STR_LEN ; 
 char* dup_mem (char*,size_t) ; 
 int /*<<< orphan*/  isoctal (char) ; 
 char* phone_num ; 
 char* phone_num2 ; 
 int quiet ; 

char *
clean(char *s, int sending)
{
    char temp[STR_LEN], cur_chr;
    char *s1, *phchar;
    int add_return = sending;
#define isoctal(chr) (((chr) >= '0') && ((chr) <= '7'))

    s1 = temp;
    /* Don't overflow buffer, leave room for chars we append later */
    while (*s && s1 - temp < (off_t)(sizeof(temp) - 2 - add_return)) {
	cur_chr = *s++;
	if (cur_chr == '^') {
	    cur_chr = *s++;
	    if (cur_chr == '\0') {
		*s1++ = '^';
		break;
	    }
	    cur_chr &= 0x1F;
	    if (cur_chr != 0) {
		*s1++ = cur_chr;
	    }
	    continue;
	}

	if (cur_chr != '\\') {
	    *s1++ = cur_chr;
	    continue;
	}

	cur_chr = *s++;
	if (cur_chr == '\0') {
	    if (sending) {
		*s1++ = '\\';
		*s1++ = '\\';
	    }
	    break;
	}

	switch (cur_chr) {
	case 'b':
	    *s1++ = '\b';
	    break;

	case 'c':
	    if (sending && *s == '\0')
		add_return = 0;
	    else
		*s1++ = cur_chr;
	    break;

	case '\\':
	case 'K':
	case 'p':
	case 'd':
	    if (sending)
		*s1++ = '\\';

	    *s1++ = cur_chr;
	    break;

	case 'T':
	    if (sending && phone_num) {
		for ( phchar = phone_num; *phchar != '\0'; phchar++) 
		    *s1++ = *phchar;
	    }
	    else {
		*s1++ = '\\';
		*s1++ = 'T';
	    }
	    break;

	case 'U':
	    if (sending && phone_num2) {
		for ( phchar = phone_num2; *phchar != '\0'; phchar++) 
		    *s1++ = *phchar;
	    }
	    else {
		*s1++ = '\\';
		*s1++ = 'U';
	    }
	    break;

	case 'q':
	    quiet = 1;
	    break;

	case 'r':
	    *s1++ = '\r';
	    break;

	case 'n':
	    *s1++ = '\n';
	    break;

	case 's':
	    *s1++ = ' ';
	    break;

	case 't':
	    *s1++ = '\t';
	    break;

	case 'N':
	    if (sending) {
		*s1++ = '\\';
		*s1++ = '\0';
	    }
	    else
		*s1++ = 'N';
	    break;
	    
	default:
	    if (isoctal (cur_chr)) {
		cur_chr &= 0x07;
		if (isoctal (*s)) {
		    cur_chr <<= 3;
		    cur_chr |= *s++ - '0';
		    if (isoctal (*s)) {
			cur_chr <<= 3;
			cur_chr |= *s++ - '0';
		    }
		}

		if (cur_chr != 0 || sending) {
		    if (sending && (cur_chr == '\\' || cur_chr == 0))
			*s1++ = '\\';
		    *s1++ = cur_chr;
		}
		break;
	    }

	    if (sending)
		*s1++ = '\\';
	    *s1++ = cur_chr;
	    break;
	}
    }

    if (add_return)
	*s1++ = '\r';

    *s1++ = '\0'; /* guarantee closure */
    *s1++ = '\0'; /* terminate the string */
    return dup_mem (temp, (size_t) (s1 - temp)); /* may have embedded nuls */
}