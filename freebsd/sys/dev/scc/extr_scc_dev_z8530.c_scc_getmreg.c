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
typedef  int /*<<< orphan*/  uint8_t ;
struct scc_bas {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_CTRL ; 
 int /*<<< orphan*/  scc_barrier (struct scc_bas*) ; 
 int /*<<< orphan*/  scc_getreg (struct scc_bas*,scalar_t__) ; 
 int /*<<< orphan*/  scc_setreg (struct scc_bas*,scalar_t__,int) ; 

__attribute__((used)) static __inline uint8_t
scc_getmreg(struct scc_bas *bas, int ch, int reg)
{

	scc_setreg(bas, ch + REG_CTRL, reg);
	scc_barrier(bas);
	return (scc_getreg(bas, ch + REG_CTRL));
}