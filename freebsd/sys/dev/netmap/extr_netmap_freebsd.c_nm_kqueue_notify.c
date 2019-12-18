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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct nm_selinfo {TYPE_1__ si; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_UNLOCKED (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nm_kqueue_notify(void *opaque, int pending)
{
	struct nm_selinfo *si = opaque;

	/* We use a non-zero hint to distinguish this notification call
	 * from the call done in kqueue_scan(), which uses hint=0.
	 */
	KNOTE_UNLOCKED(&si->si.si_note, /*hint=*/0x100);
}