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
struct sshkey {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int sshkey_read (struct sshkey*,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
sshkey_try_load_public(struct sshkey *k, const char *filename, char **commentp)
{
	FILE *f;
	char *line = NULL, *cp;
	size_t linesize = 0;
	int r;

	if (commentp != NULL)
		*commentp = NULL;
	if ((f = fopen(filename, "r")) == NULL)
		return SSH_ERR_SYSTEM_ERROR;
	while (getline(&line, &linesize, f) != -1) {
		cp = line;
		switch (*cp) {
		case '#':
		case '\n':
		case '\0':
			continue;
		}
		/* Abort loading if this looks like a private key */
		if (strncmp(cp, "-----BEGIN", 10) == 0 ||
		    strcmp(cp, "SSH PRIVATE KEY FILE") == 0)
			break;
		/* Skip leading whitespace. */
		for (; *cp && (*cp == ' ' || *cp == '\t'); cp++)
			;
		if (*cp) {
			if ((r = sshkey_read(k, &cp)) == 0) {
				cp[strcspn(cp, "\r\n")] = '\0';
				if (commentp) {
					*commentp = strdup(*cp ?
					    cp : filename);
					if (*commentp == NULL)
						r = SSH_ERR_ALLOC_FAIL;
				}
				free(line);
				fclose(f);
				return r;
			}
		}
	}
	free(line);
	fclose(f);
	return SSH_ERR_INVALID_FORMAT;
}