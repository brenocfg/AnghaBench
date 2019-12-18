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
 int ENXIO ; 
 scalar_t__ SBBC_CONS_MAGIC ; 
 scalar_t__ SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 scalar_t__ SBBC_CONS_VERSION ; 
 scalar_t__ SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  cons_magic ; 
 int /*<<< orphan*/  cons_version ; 
 int sbbc_console ; 
 int sbbc_parse_toc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sbbc_scsolie ; 
 scalar_t__ sbbc_scsolir ; 
 scalar_t__ sbbc_solcons ; 
 scalar_t__ sbbc_solscie ; 
 scalar_t__ sbbc_solscir ; 

__attribute__((used)) static int
sbbc_uart_probe(struct uart_bas *bas)
{
	bus_space_tag_t bst;
	bus_space_handle_t bsh;
	int error;

	sbbc_console = 1;
	bst = bas->bst;
	bsh = bas->bsh;
	error = sbbc_parse_toc(bst, bsh);
	if (error != 0)
		return (error);

	if (sbbc_scsolie == 0 || sbbc_scsolir == 0 || sbbc_solcons == 0 ||
	    sbbc_solscie == 0 || sbbc_solscir == 0)
		return (ENXIO);

	if (SBBC_SRAM_READ_4(sbbc_solcons + SBBC_CONS_OFF(cons_magic)) !=
	    SBBC_CONS_MAGIC || SBBC_SRAM_READ_4(sbbc_solcons +
	    SBBC_CONS_OFF(cons_version)) < SBBC_CONS_VERSION)
		return (ENXIO);
	return (0);
}