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
struct macalg {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 struct macalg* macs ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

char *
mac_alg_list(char sep)
{
	char *ret = NULL, *tmp;
	size_t nlen, rlen = 0;
	const struct macalg *m;

	for (m = macs; m->name != NULL; m++) {
		if (ret != NULL)
			ret[rlen++] = sep;
		nlen = strlen(m->name);
		if ((tmp = realloc(ret, rlen + nlen + 2)) == NULL) {
			free(ret);
			return NULL;
		}
		ret = tmp;
		memcpy(ret + rlen, m->name, nlen + 1);
		rlen += nlen;
	}
	return ret;
}