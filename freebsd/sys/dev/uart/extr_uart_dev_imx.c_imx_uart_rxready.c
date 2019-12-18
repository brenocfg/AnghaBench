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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDR ; 
 int /*<<< orphan*/  USR2 ; 

__attribute__((used)) static int
imx_uart_rxready(struct uart_bas *bas)
{

	return ((IS(bas, USR2, RDR)) ? 1 : 0);
}