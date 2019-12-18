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
struct system_segment_descriptor {int /*<<< orphan*/  sd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPROC0_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct system_segment_descriptor* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDT_SYSTSS ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  ltr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tss ; 

__attribute__((used)) static __inline void
restore_host_tss(void)
{
	struct system_segment_descriptor *tss_sd;

	/*
	 * The TSS descriptor was in use prior to launching the guest so it
	 * has been marked busy.
	 *
	 * 'ltr' requires the descriptor to be marked available so change the
	 * type to "64-bit available TSS".
	 */
	tss_sd = PCPU_GET(tss);
	tss_sd->sd_type = SDT_SYSTSS;
	ltr(GSEL(GPROC0_SEL, SEL_KPL));
}