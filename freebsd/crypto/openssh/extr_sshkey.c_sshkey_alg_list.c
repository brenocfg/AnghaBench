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
struct keytype {int type; int /*<<< orphan*/ * name; scalar_t__ cert; scalar_t__ sigonly; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 struct keytype* keytypes ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

char *
sshkey_alg_list(int certs_only, int plain_only, int include_sigonly, char sep)
{
	char *tmp, *ret = NULL;
	size_t nlen, rlen = 0;
	const struct keytype *kt;

	for (kt = keytypes; kt->type != -1; kt++) {
		if (kt->name == NULL)
			continue;
		if (!include_sigonly && kt->sigonly)
			continue;
		if ((certs_only && !kt->cert) || (plain_only && kt->cert))
			continue;
		if (ret != NULL)
			ret[rlen++] = sep;
		nlen = strlen(kt->name);
		if ((tmp = realloc(ret, rlen + nlen + 2)) == NULL) {
			free(ret);
			return NULL;
		}
		ret = tmp;
		memcpy(ret + rlen, kt->name, nlen + 1);
		rlen += nlen;
	}
	return ret;
}