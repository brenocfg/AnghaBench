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
 int /*<<< orphan*/  GC_LOCK () ; 
 int /*<<< orphan*/  GC_UNLOCK () ; 
 int /*<<< orphan*/  gxemul_cons_write (int) ; 

__attribute__((used)) static void
gxemul_cons_cnputc(struct consdev *cp, int c)
{

	GC_LOCK();
	gxemul_cons_write(c);
	GC_UNLOCK();
}