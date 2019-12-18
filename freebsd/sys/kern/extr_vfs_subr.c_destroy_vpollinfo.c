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
struct vpollinfo {TYPE_1__ vpi_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_vpollinfo_free (struct vpollinfo*) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static void
destroy_vpollinfo(struct vpollinfo *vi)
{

	knlist_clear(&vi->vpi_selinfo.si_note, 1);
	seldrain(&vi->vpi_selinfo);
	destroy_vpollinfo_free(vi);
}