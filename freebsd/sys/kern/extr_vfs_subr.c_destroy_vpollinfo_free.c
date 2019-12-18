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
struct vpollinfo {int /*<<< orphan*/  vpi_lock; TYPE_1__ vpi_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct vpollinfo*) ; 
 int /*<<< orphan*/  vnodepoll_zone ; 

__attribute__((used)) static void
destroy_vpollinfo_free(struct vpollinfo *vi)
{

	knlist_destroy(&vi->vpi_selinfo.si_note);
	mtx_destroy(&vi->vpi_lock);
	uma_zfree(vnodepoll_zone, vi);
}