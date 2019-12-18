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
struct consdev {void* cn_arg; } ;

/* Variables and functions */
 size_t DCONS_CON ; 
 int /*<<< orphan*/  dcons_drv_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sc ; 

__attribute__((used)) static void
dcons_cninit(struct consdev *cp)
{
	dcons_drv_init(0);
	cp->cn_arg = (void *)&sc[DCONS_CON]; /* share port0 with unit0 */
}