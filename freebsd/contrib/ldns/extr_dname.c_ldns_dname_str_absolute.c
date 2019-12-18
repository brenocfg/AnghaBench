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

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

bool
ldns_dname_str_absolute(const char *dname_str)
{
        const char* s;
	if(dname_str && strcmp(dname_str, ".") == 0)
		return 1;
        if(!dname_str || strlen(dname_str) < 2)
                return 0;
        if(dname_str[strlen(dname_str) - 1] != '.')
                return 0;
        if(dname_str[strlen(dname_str) - 2] != '\\')
                return 1; /* ends in . and no \ before it */
        /* so we have the case of ends in . and there is \ before it */
        for(s=dname_str; *s; s++) {
                if(*s == '\\') {
                        if(s[1] && s[2] && s[3] /* check length */
                                && isdigit((unsigned char)s[1])
				&& isdigit((unsigned char)s[2])
				&& isdigit((unsigned char)s[3]))
                                s += 3;
                        else if(!s[1] || isdigit((unsigned char)s[1])) /* escape of nul,0-9 */
                                return 0; /* parse error */
                        else s++; /* another character escaped */
                }
                else if(!*(s+1) && *s == '.')
                        return 1; /* trailing dot, unescaped */
        }
        return 0;
}