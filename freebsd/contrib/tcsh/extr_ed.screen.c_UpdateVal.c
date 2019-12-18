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
typedef  char Char ;

/* Variables and functions */
 char* Itoa (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Strcat (char*,char*) ; 
 char* Strchr (char*,char) ; 
 int /*<<< orphan*/  Strcpy (char*,char*) ; 
 int Strlen (char const*) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 char* Strstr (char*,char const*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static int
UpdateVal(const Char *tag, int value, Char *termcap, Char *backup)
{
    Char *ptr, *p;
    if ((ptr = Strstr(termcap, tag)) == NULL) {
	(void)Strcpy(backup, termcap);
	return 0;
    } else {
	size_t len = (ptr - termcap) + Strlen(tag);
	(void)Strncpy(backup, termcap, len);
	backup[len] = '\0';
	p = Itoa(value, 0, 0);
	(void) Strcat(backup + len, p);
	xfree(p);
	ptr = Strchr(ptr, ':');
	if (ptr)
	    (void) Strcat(backup, ptr);
	return 1;
    }
}