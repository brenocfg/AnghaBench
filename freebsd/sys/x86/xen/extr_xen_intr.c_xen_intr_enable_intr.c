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
struct xenisrc {int /*<<< orphan*/  xi_port; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evtchn_unmask_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xen_intr_enable_intr(struct intsrc *base_isrc)
{
	struct xenisrc *isrc = (struct xenisrc *)base_isrc;

	evtchn_unmask_port(isrc->xi_port);
}