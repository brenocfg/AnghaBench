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
typedef  int /*<<< orphan*/  uint64_t ;
struct ioat_softc {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHAINADDR_OFFSET_LOW ; 
 scalar_t__ IOAT_VER_3_3 ; 
 int /*<<< orphan*/  ioat_write_8 (struct ioat_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_write_double_4 (struct ioat_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ioat_write_chainaddr(struct ioat_softc *ioat, uint64_t addr)
{

	if (ioat->version >= IOAT_VER_3_3)
		ioat_write_8(ioat, IOAT_CHAINADDR_OFFSET_LOW, addr);
	else
		ioat_write_double_4(ioat, IOAT_CHAINADDR_OFFSET_LOW, addr);
}