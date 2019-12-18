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
struct mce {int bank; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int XEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  report_gart_errors ; 

__attribute__((used)) static bool ignore_mce(struct mce *m)
{
	/*
	 * NB GART TLB error reporting is disabled by default.
	 */
	if (m->bank == 4 && XEC(m->status, 0x1f) == 0x5 && !report_gart_errors)
		return true;

	return false;
}