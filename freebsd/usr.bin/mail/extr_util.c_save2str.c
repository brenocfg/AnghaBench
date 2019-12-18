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
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 char* salloc (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
save2str(char *str, char *old)
{
	char *new;
	int newsize = strlen(str) + 1;
	int oldsize = old ? strlen(old) + 1 : 0;

	if ((new = salloc(newsize + oldsize)) != NULL) {
		if (oldsize) {
			bcopy(old, new, oldsize);
			new[oldsize - 1] = ' ';
		}
		bcopy(str, new + oldsize, newsize);
	}
	return (new);
}