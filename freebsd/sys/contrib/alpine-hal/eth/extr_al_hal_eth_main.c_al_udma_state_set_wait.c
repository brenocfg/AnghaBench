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
struct al_udma {int /*<<< orphan*/  name; } ;
typedef  enum al_udma_state { ____Placeholder_al_udma_state } al_udma_state ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int UDMA_DISABLE ; 
 int UDMA_IDLE ; 
 int UDMA_NORMAL ; 
 int /*<<< orphan*/  al_udelay (int) ; 
 int al_udma_state_get (struct al_udma*) ; 
 int al_udma_state_set (struct al_udma*,int) ; 
 int* al_udma_states_name ; 
 int /*<<< orphan*/  al_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int al_udma_state_set_wait(struct al_udma *dma, enum al_udma_state new_state)
{
	enum al_udma_state state;
	enum al_udma_state expected_state = new_state;
	int count = 1000;
	int rc;

	rc = al_udma_state_set(dma, new_state);
	if (rc != 0) {
		al_warn("[%s] warn: failed to change state, error %d\n", dma->name, rc);
		return rc;
	}

	if ((new_state == UDMA_NORMAL) || (new_state == UDMA_DISABLE))
		expected_state = UDMA_IDLE;

	do {
		state = al_udma_state_get(dma);
		if (state == expected_state)
			break;
		al_udelay(1);
		if (count-- == 0) {
			al_warn("[%s] warn: dma state didn't change to %s\n",
				 dma->name, al_udma_states_name[new_state]);
			return -ETIMEDOUT;
		}
	} while (1);
	return 0;
}