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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
mknum(char *str, char ch)
{
	static char *copy;
	static size_t copy_size;
	char *newcopy;
	size_t len, newlen;

	len = strlen(str) + 2;
	if (len > copy_size) {
		newlen = ((len + 1023) >> 10) << 10;
		if ((newcopy = realloc(copy, newlen)) == NULL) {
			warnx("%s", strerror(ENOMEM));
			return (NULL);
		}
		copy = newcopy;
		copy_size = newlen;
	}

	memmove(copy, str, len - 3);
	copy[len - 3] = 'j';
	copy[len - 2] = ch;
	copy[len - 1] = '\0';
	return (copy);
}