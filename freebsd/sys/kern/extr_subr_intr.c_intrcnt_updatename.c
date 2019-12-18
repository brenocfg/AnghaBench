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
struct intr_irqsrc {int /*<<< orphan*/  isrc_index; TYPE_1__* isrc_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  ie_fullname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  intrcnt_setname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isrc_table_lock ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intrcnt_updatename(struct intr_irqsrc *isrc)
{

	/* QQQ: What about stray counter name? */
	mtx_assert(&isrc_table_lock, MA_OWNED);
	intrcnt_setname(isrc->isrc_event->ie_fullname, isrc->isrc_index);
}