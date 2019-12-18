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

/* Variables and functions */
 int /*<<< orphan*/  MCF_SCM_BCR ; 
 int MCF_SCM_BCR_GBR ; 
 int MCF_SCM_BCR_GBW ; 
 int /*<<< orphan*/  MCF_SCM_MPR ; 
 int /*<<< orphan*/  MCF_SCM_PACRA ; 
 int /*<<< orphan*/  MCF_SCM_PACRB ; 
 int /*<<< orphan*/  MCF_SCM_PACRC ; 
 int /*<<< orphan*/  MCF_SCM_PACRD ; 
 int /*<<< orphan*/  MCF_SCM_PACRE ; 
 int /*<<< orphan*/  MCF_SCM_PACRF ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void scm_init(void)
{
	/* All masters are trusted */
	writel(0x77777777, MCF_SCM_MPR);
    
	/* Allow supervisor/user, read/write, and trusted/untrusted
	   access to all slaves */
	writel(0, MCF_SCM_PACRA);
	writel(0, MCF_SCM_PACRB);
	writel(0, MCF_SCM_PACRC);
	writel(0, MCF_SCM_PACRD);
	writel(0, MCF_SCM_PACRE);
	writel(0, MCF_SCM_PACRF);

	/* Enable bursts */
	writel(MCF_SCM_BCR_GBR | MCF_SCM_BCR_GBW, MCF_SCM_BCR);
}