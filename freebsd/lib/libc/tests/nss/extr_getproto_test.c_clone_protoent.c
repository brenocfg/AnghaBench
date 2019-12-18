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
struct protoent {char* p_name; char** p_aliases; int /*<<< orphan*/  p_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  memset (struct protoent*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static void
clone_protoent(struct protoent *dest, struct protoent const *src)
{
	assert(dest != NULL);
	assert(src != NULL);

	char **cp;
	int aliases_num;

	memset(dest, 0, sizeof(struct protoent));

	if (src->p_name != NULL) {
		dest->p_name = strdup(src->p_name);
		assert(dest->p_name != NULL);
	}

	dest->p_proto = src->p_proto;

	if (src->p_aliases != NULL) {
		aliases_num = 0;
		for (cp = src->p_aliases; *cp; ++cp)
			++aliases_num;

		dest->p_aliases = calloc(aliases_num + 1, sizeof(char *));
		assert(dest->p_aliases != NULL);

		for (cp = src->p_aliases; *cp; ++cp) {
			dest->p_aliases[cp - src->p_aliases] = strdup(*cp);
			assert(dest->p_aliases[cp - src->p_aliases] != NULL);
		}
	}
}