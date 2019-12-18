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
 int APC_IDLE_ON ; 
 int /*<<< orphan*/  APC_IDLE_REG ; 
 int AUXIO_LED ; 
 int apc_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apc_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_auxio (int,int) ; 

__attribute__((used)) static void apc_swift_idle(void)
{
#ifdef APC_DEBUG_LED
	set_auxio(0x00, AUXIO_LED); 
#endif

	apc_writeb(apc_readb(APC_IDLE_REG) | APC_IDLE_ON, APC_IDLE_REG);

#ifdef APC_DEBUG_LED
	set_auxio(AUXIO_LED, 0x00); 
#endif
}