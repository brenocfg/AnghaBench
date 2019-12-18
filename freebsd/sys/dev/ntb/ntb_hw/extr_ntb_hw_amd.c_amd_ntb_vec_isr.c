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
struct amd_ntb_vec {int /*<<< orphan*/  num; int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_ntb_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amd_ntb_vec_isr(void *arg)
{
	struct amd_ntb_vec *nvec = arg;

	amd_ntb_interrupt(nvec->ntb, nvec->num);
}