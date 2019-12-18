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
struct sshcipher {int flags; } ;

/* Variables and functions */
 int CFLAG_INTERNAL ; 
 int /*<<< orphan*/  CIPHER_SEP ; 
 struct sshcipher* cipher_by_name (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 

int
ciphers_valid(const char *names)
{
	const struct sshcipher *c;
	char *cipher_list, *cp;
	char *p;

	if (names == NULL || strcmp(names, "") == 0)
		return 0;
	if ((cipher_list = cp = strdup(names)) == NULL)
		return 0;
	for ((p = strsep(&cp, CIPHER_SEP)); p && *p != '\0';
	    (p = strsep(&cp, CIPHER_SEP))) {
		c = cipher_by_name(p);
		if (c == NULL || (c->flags & CFLAG_INTERNAL) != 0) {
			free(cipher_list);
			return 0;
		}
	}
	free(cipher_list);
	return 1;
}