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
typedef  size_t vci_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* unqueue ) (struct lanai_dev*,struct lanai_vcc*,int) ;int /*<<< orphan*/ * atmvcc; } ;
struct lanai_vcc {TYPE_1__ tx; } ;
struct lanai_dev {int /*<<< orphan*/  backlog_vccs; struct lanai_vcc** vccs; } ;

/* Variables and functions */
 int TXREADPTR_GET_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cardvcc_read (struct lanai_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct lanai_dev*,struct lanai_vcc*,int) ; 
 int /*<<< orphan*/  vcc_is_backlogged (struct lanai_vcc*) ; 
 int /*<<< orphan*/  vcc_txreadptr ; 

__attribute__((used)) static void iter_dequeue(struct lanai_dev *lanai, vci_t vci)
{
	struct lanai_vcc *lvcc = lanai->vccs[vci];
	int endptr;
	if (lvcc == NULL || lvcc->tx.atmvcc == NULL ||
	    !vcc_is_backlogged(lvcc)) {
		__clear_bit(vci, lanai->backlog_vccs);
		return;
	}
	endptr = TXREADPTR_GET_PTR(cardvcc_read(lvcc, vcc_txreadptr));
	lvcc->tx.unqueue(lanai, lvcc, endptr);
}