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
struct search_state {int refcount; int ndots; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct search_state*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mm_malloc (int) ; 

__attribute__((used)) static struct search_state *
search_state_new(void) {
	struct search_state *state = (struct search_state *) mm_malloc(sizeof(struct search_state));
	if (!state) return NULL;
	memset(state, 0, sizeof(struct search_state));
	state->refcount = 1;
	state->ndots = 1;

	return state;
}