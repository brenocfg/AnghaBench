#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_map {int dummy; } ;
struct idt77252_dev {unsigned long* tst; int tst_index; int tst_size; TYPE_1__* soft_tst; int /*<<< orphan*/  tst_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  tste; struct vc_map* vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSTE_OPC_VAR ; 
 int /*<<< orphan*/  TSTE_PUSH_ACTIVE ; 
 int /*<<< orphan*/  TSTE_PUSH_IDLE ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__clear_tst(struct idt77252_dev *card, struct vc_map *vc)
{
	unsigned long idle;
	int e;

	idle = card->tst[card->tst_index ^ 1];

	for (e = 0; e < card->tst_size - 2; e++) {
		if (card->soft_tst[e].vc == vc) {
			card->soft_tst[e].vc = NULL;

			card->soft_tst[e].tste = TSTE_OPC_VAR;
			if (timer_pending(&card->tst_timer))
				card->soft_tst[e].tste |= TSTE_PUSH_ACTIVE;
			else {
				write_sram(card, idle + e, TSTE_OPC_VAR);
				card->soft_tst[e].tste |= TSTE_PUSH_IDLE;
			}
		}
	}

	return 0;
}