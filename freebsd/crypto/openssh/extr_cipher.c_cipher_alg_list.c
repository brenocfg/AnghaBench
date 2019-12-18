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
struct sshcipher {int flags; scalar_t__ auth_len; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int CFLAG_INTERNAL ; 
 struct sshcipher* ciphers ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

char *
cipher_alg_list(char sep, int auth_only)
{
	char *tmp, *ret = NULL;
	size_t nlen, rlen = 0;
	const struct sshcipher *c;

	for (c = ciphers; c->name != NULL; c++) {
		if ((c->flags & CFLAG_INTERNAL) != 0)
			continue;
		if (auth_only && c->auth_len == 0)
			continue;
		if (ret != NULL)
			ret[rlen++] = sep;
		nlen = strlen(c->name);
		if ((tmp = realloc(ret, rlen + nlen + 2)) == NULL) {
			free(ret);
			return NULL;
		}
		ret = tmp;
		memcpy(ret + rlen, c->name, nlen + 1);
		rlen += nlen;
	}
	return ret;
}