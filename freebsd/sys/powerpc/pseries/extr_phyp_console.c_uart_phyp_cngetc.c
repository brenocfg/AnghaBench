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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alt_break_state ; 
 int /*<<< orphan*/  console_sc ; 
 int /*<<< orphan*/  kdb_alt_break (unsigned char,int /*<<< orphan*/ *) ; 
 int uart_phyp_get (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
uart_phyp_cngetc(struct consdev *cp)
{
	unsigned char c;
	int retval;

	retval = uart_phyp_get(console_sc, &c, 1);
	if (retval != 1)
		return (-1);
#if defined(KDB)
	kdb_alt_break(c, &alt_break_state);
#endif

	return (c);
}