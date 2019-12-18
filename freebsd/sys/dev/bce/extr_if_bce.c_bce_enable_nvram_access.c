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
typedef  int u32 ;
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_NVM_ACCESS_ENABLE ; 
 int BCE_NVM_ACCESS_ENABLE_EN ; 
 int BCE_NVM_ACCESS_ENABLE_WR_EN ; 
 int /*<<< orphan*/  BCE_VERBOSE_NVRAM ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int REG_RD (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bce_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bce_enable_nvram_access(struct bce_softc *sc)
{
	u32 val;

	DBENTER(BCE_VERBOSE_NVRAM);

	val = REG_RD(sc, BCE_NVM_ACCESS_ENABLE);
	/* Enable both bits, even on read. */
	REG_WR(sc, BCE_NVM_ACCESS_ENABLE, val |
	    BCE_NVM_ACCESS_ENABLE_EN | BCE_NVM_ACCESS_ENABLE_WR_EN);

	DBEXIT(BCE_VERBOSE_NVRAM);
}