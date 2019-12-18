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

/* Variables and functions */
 scalar_t__ GXEMUL_CONS_BASE ; 
 scalar_t__ GXEMUL_PUTGETCHAR_OFF ; 
 int /*<<< orphan*/  mips_ioread_uint8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_phys_to_uncached (scalar_t__) ; 

__attribute__((used)) static inline uint8_t
gxemul_cons_data_read(void)
{

	return (mips_ioread_uint8(mips_phys_to_uncached(GXEMUL_CONS_BASE +
	    GXEMUL_PUTGETCHAR_OFF)));
}