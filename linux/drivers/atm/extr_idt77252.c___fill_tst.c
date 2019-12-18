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
typedef  unsigned int u32 ;
struct vc_map {int index; } ;
struct idt77252_dev {int tst_size; unsigned long* tst; int tst_index; TYPE_1__* soft_tst; int /*<<< orphan*/  tst_timer; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {unsigned int tste; struct vc_map* vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPRINTK (char*,int /*<<< orphan*/ ,int,int) ; 
 unsigned int TSTE_OPC_MASK ; 
 unsigned int TSTE_OPC_NULL ; 
 unsigned int TSTE_PUSH_ACTIVE ; 
 unsigned int TSTE_PUSH_IDLE ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,unsigned long,unsigned int) ; 

__attribute__((used)) static int
__fill_tst(struct idt77252_dev *card, struct vc_map *vc,
	   int n, unsigned int opc)
{
	unsigned long cl, avail;
	unsigned long idle;
	int e, r;
	u32 data;

	avail = card->tst_size - 2;
	for (e = 0; e < avail; e++) {
		if (card->soft_tst[e].vc == NULL)
			break;
	}
	if (e >= avail) {
		printk("%s: No free TST entries found\n", card->name);
		return -1;
	}

	NPRINTK("%s: conn %d: first TST entry at %d.\n",
		card->name, vc ? vc->index : -1, e);

	r = n;
	cl = avail;
	data = opc & TSTE_OPC_MASK;
	if (vc && (opc != TSTE_OPC_NULL))
		data = opc | vc->index;

	idle = card->tst[card->tst_index ^ 1];

	/*
	 * Fill Soft TST.
	 */
	while (r > 0) {
		if ((cl >= avail) && (card->soft_tst[e].vc == NULL)) {
			if (vc)
				card->soft_tst[e].vc = vc;
			else
				card->soft_tst[e].vc = (void *)-1;

			card->soft_tst[e].tste = data;
			if (timer_pending(&card->tst_timer))
				card->soft_tst[e].tste |= TSTE_PUSH_ACTIVE;
			else {
				write_sram(card, idle + e, data);
				card->soft_tst[e].tste |= TSTE_PUSH_IDLE;
			}

			cl -= card->tst_size;
			r--;
		}

		if (++e == avail)
			e = 0;
		cl += n;
	}

	return 0;
}