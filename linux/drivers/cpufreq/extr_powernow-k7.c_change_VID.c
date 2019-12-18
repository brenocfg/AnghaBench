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
struct TYPE_2__ {int VID; int VIDC; scalar_t__ FIDC; int /*<<< orphan*/  SGTC; } ;
union msr_fidvidctl {int /*<<< orphan*/  val; TYPE_1__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K7_FID_VID_CTL ; 
 int /*<<< orphan*/  latency ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void change_VID(int vid)
{
	union msr_fidvidctl fidvidctl;

	rdmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	if (fidvidctl.bits.VID != vid) {
		fidvidctl.bits.SGTC = latency;
		fidvidctl.bits.VID = vid;
		fidvidctl.bits.FIDC = 0;
		fidvidctl.bits.VIDC = 1;
		wrmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	}
}