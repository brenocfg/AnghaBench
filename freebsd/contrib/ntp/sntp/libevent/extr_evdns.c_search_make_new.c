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
typedef  char u8 ;
struct search_state {struct search_domain* head; } ;
struct search_domain {int len; struct search_domain* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char* const,char const* const,int const) ; 
 scalar_t__ mm_malloc (size_t const) ; 
 size_t strlen (char const* const) ; 

__attribute__((used)) static char *
search_make_new(const struct search_state *const state, int n, const char *const base_name) {
	const size_t base_len = strlen(base_name);
	const char need_to_append_dot = base_name[base_len - 1] == '.' ? 0 : 1;
	struct search_domain *dom;

	for (dom = state->head; dom; dom = dom->next) {
		if (!n--) {
			/* this is the postfix we want */
			/* the actual postfix string is kept at the end of the structure */
			const u8 *const postfix = ((u8 *) dom) + sizeof(struct search_domain);
			const int postfix_len = dom->len;
			char *const newname = (char *) mm_malloc(base_len + need_to_append_dot + postfix_len + 1);
			if (!newname) return NULL;
			memcpy(newname, base_name, base_len);
			if (need_to_append_dot) newname[base_len] = '.';
			memcpy(newname + base_len + need_to_append_dot, postfix, postfix_len);
			newname[base_len + need_to_append_dot + postfix_len] = 0;
			return newname;
		}
	}

	/* we ran off the end of the list and still didn't find the requested string */
	EVUTIL_ASSERT(0);
	return NULL; /* unreachable; stops warnings in some compilers. */
}