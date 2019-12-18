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
typedef  scalar_t__ u_int ;
struct cfi_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ AMD_ADDR_ACK ; 
 scalar_t__ AMD_ADDR_START ; 
 scalar_t__ CFI_AMD_UNLOCK ; 
 scalar_t__ CFI_AMD_UNLOCK_ACK ; 
 int /*<<< orphan*/  cfi_write (struct cfi_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
cfi_amd_write(struct cfi_softc *sc, u_int ofs, u_int addr, u_int data)
{

	cfi_write(sc, ofs + AMD_ADDR_START, CFI_AMD_UNLOCK);
	cfi_write(sc, ofs + AMD_ADDR_ACK, CFI_AMD_UNLOCK_ACK);
	cfi_write(sc, ofs + addr, data);
}