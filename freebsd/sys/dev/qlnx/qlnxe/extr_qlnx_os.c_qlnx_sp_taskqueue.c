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
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlnx_sp_isr (struct ecore_hwfn*) ; 

__attribute__((used)) static void
qlnx_sp_taskqueue(void *context, int pending)
{
	struct ecore_hwfn	*p_hwfn;

	p_hwfn = context;

	if (p_hwfn != NULL) {
		qlnx_sp_isr(p_hwfn);
	}
	return;
}