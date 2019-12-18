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
struct fileptr {char* s; int /*<<< orphan*/ * f; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 char* fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int strcspn (char*,char*) ; 

__attribute__((used)) static char *
config_fgets(char *str, size_t len, struct fileptr *ptr)
{
    /* XXX this is not correct, in that they don't do the same if the
       line is longer than len */
    if(ptr->f != NULL)
	return fgets(str, len, ptr->f);
    else {
	/* this is almost strsep_copy */
	const char *p;
	ssize_t l;
	if(*ptr->s == '\0')
	    return NULL;
	p = ptr->s + strcspn(ptr->s, "\n");
	if(*p == '\n')
	    p++;
	l = min(len, (size_t)(p - ptr->s));
	if(len > 0) {
	    memcpy(str, ptr->s, l);
	    str[l] = '\0';
	}
	ptr->s = p;
	return str;
    }
}