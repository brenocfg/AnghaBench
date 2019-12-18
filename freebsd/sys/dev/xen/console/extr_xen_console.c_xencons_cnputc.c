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
 int /*<<< orphan*/  main_cons ; 
 int /*<<< orphan*/  xencons_putc (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
xencons_cnputc(struct consdev *dev, int c)
{
	/*
	 * The low-level console is used by KDB and panic. We have to ensure
	 * that any character sent will be seen by the backend.
	 */
	xencons_putc(&main_cons, c, true);
}