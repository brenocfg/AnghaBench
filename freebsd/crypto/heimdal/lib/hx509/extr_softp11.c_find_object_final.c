#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t num_attributes; int next_object; TYPE_2__* attributes; } ;
struct session_state {TYPE_1__ find; } ;
struct TYPE_4__ {struct TYPE_4__* pValue; } ;
typedef  size_t CK_ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
find_object_final(struct session_state *state)
{
    if (state->find.attributes) {
	CK_ULONG i;

	for (i = 0; i < state->find.num_attributes; i++) {
	    if (state->find.attributes[i].pValue)
		free(state->find.attributes[i].pValue);
	}
	free(state->find.attributes);
	state->find.attributes = NULL;
	state->find.num_attributes = 0;
	state->find.next_object = -1;
    }
}