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
typedef  int uint32_t ;
struct uart_bas {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 int SBBC_SRAM_CONS_OUT ; 
 int SBBC_SRAM_READ_4 (int) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_1 (int,int) ; 
 int /*<<< orphan*/  SBBC_SRAM_WRITE_4 (int,int) ; 
 int /*<<< orphan*/  cons_out_begin ; 
 int /*<<< orphan*/  cons_out_end ; 
 int /*<<< orphan*/  cons_out_wrptr ; 
 int /*<<< orphan*/  sbbc_send_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sbbc_solcons ; 
 int sbbc_solscir ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 

__attribute__((used)) static void
sbbc_uart_putc(struct uart_bas *bas, int c)
{
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	uint32_t wrptr;

	bst = bas->bst;
	bsh = bas->bsh;

	wrptr = SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_out_wrptr));
	SBBC_SRAM_WRITE_1(sbbc_solcons + wrptr, c);
	uart_barrier(bas);
	if (++wrptr == SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_out_end)))
		wrptr = SBBC_SRAM_READ_4(sbbc_solcons +
		    SBBC_CONS_OFF(cons_out_begin));
	SBBC_SRAM_WRITE_4(sbbc_solcons + SBBC_CONS_OFF(cons_out_wrptr),
	    wrptr);
	uart_barrier(bas);

	SBBC_SRAM_WRITE_4(sbbc_solscir, SBBC_SRAM_READ_4(sbbc_solscir) |
	    SBBC_SRAM_CONS_OUT);
	uart_barrier(bas);
	sbbc_send_intr(bst, bsh);
}