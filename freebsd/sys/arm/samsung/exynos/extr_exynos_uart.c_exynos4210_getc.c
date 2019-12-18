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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCOM_URXH ; 
 int /*<<< orphan*/  SSCOM_UTRSTAT ; 
 int UTRSTAT_RXREADY ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exynos4210_getc(struct uart_bas *bas, struct mtx *mtx)
{
	int utrstat;

	utrstat = bus_space_read_1(bas->bst, bas->bsh, SSCOM_UTRSTAT);
	while (!(utrstat & UTRSTAT_RXREADY)) {
		utrstat = bus_space_read_1(bas->bst, bas->bsh, SSCOM_UTRSTAT);
		continue;
	}

	return (bus_space_read_1(bas->bst, bas->bsh, SSCOM_URXH));
}