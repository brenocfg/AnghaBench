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
typedef  int uint16_t ;
struct uart_bas {scalar_t__ chan; } ;

/* Variables and functions */
 int QUICC_PRAM_SCC_RBASE (scalar_t__) ; 
 int quicc_read2 (struct uart_bas*,int) ; 

__attribute__((used)) static int
quicc_rxready(struct uart_bas *bas)
{
	uint16_t rb;

	rb = quicc_read2(bas, QUICC_PRAM_SCC_RBASE(bas->chan - 1));
	return ((quicc_read2(bas, rb) & 0x8000) ? 0 : 1);
}