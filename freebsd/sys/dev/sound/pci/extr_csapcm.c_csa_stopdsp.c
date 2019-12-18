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
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_SPCR ; 
 int /*<<< orphan*/  csa_writemem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csa_stopdsp(csa_res *resp)
{
	/*
	 * Turn off the run, run at frame, and DMA enable bits in
	 * the local copy of the SP control register.
	 */
	csa_writemem(resp, BA1_SPCR, 0);

	return (0);
}