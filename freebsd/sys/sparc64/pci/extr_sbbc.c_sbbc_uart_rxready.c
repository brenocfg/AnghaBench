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
struct uart_bas {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 scalar_t__ SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  cons_in_rdptr ; 
 int /*<<< orphan*/  cons_in_wrptr ; 
 scalar_t__ sbbc_solcons ; 

__attribute__((used)) static int
sbbc_uart_rxready(struct uart_bas *bas)
{
	bus_space_tag_t bst;
	bus_space_handle_t bsh;

	bst = bas->bst;
	bsh = bas->bsh;

	if (SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_in_rdptr)) ==
	    SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_in_wrptr)))
		return (0);
	return (1);
}