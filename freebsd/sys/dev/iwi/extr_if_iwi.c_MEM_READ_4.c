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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWI_CSR_INDIRECT_ADDR ; 
 int /*<<< orphan*/  IWI_CSR_INDIRECT_DATA ; 

__attribute__((used)) static __inline uint32_t
MEM_READ_4(struct iwi_softc *sc, uint32_t addr)
{
	CSR_WRITE_4(sc, IWI_CSR_INDIRECT_ADDR, addr);
	return CSR_READ_4(sc, IWI_CSR_INDIRECT_DATA);
}