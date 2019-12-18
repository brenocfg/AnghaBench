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
struct al_udma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_UDMA_PRINT_REG (struct al_udma*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_dbg (char*) ; 
 int /*<<< orphan*/  gen_cfg ; 
 int /*<<< orphan*/  m2s ; 
 int /*<<< orphan*/  m2s_rate_limiter ; 

__attribute__((used)) static void al_udma_regs_m2s_rate_limiter_print(struct al_udma *udma)
{
	al_dbg("M2S rate limiter regs:\n");
	AL_UDMA_PRINT_REG(udma, " ", "\n", m2s, m2s_rate_limiter, gen_cfg);
}