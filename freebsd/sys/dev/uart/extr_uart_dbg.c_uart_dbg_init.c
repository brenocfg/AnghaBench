#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DEV_DBGPORT ; 
 int /*<<< orphan*/  uart_add_sysdev (TYPE_1__*) ; 
 TYPE_1__ uart_dbgport ; 
 int /*<<< orphan*/  uart_init (TYPE_1__*) ; 

__attribute__((used)) static void
uart_dbg_init(void)
{

	uart_dbgport.type = UART_DEV_DBGPORT;
	uart_add_sysdev(&uart_dbgport);
	uart_init(&uart_dbgport);
}