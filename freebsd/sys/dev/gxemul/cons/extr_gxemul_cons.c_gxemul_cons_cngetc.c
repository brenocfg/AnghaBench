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
 int gxemul_cons_read () ; 

__attribute__((used)) static int
gxemul_cons_cngetc(struct consdev *cp)
{
	int ret;

	GC_LOCK();
	ret = gxemul_cons_read();
	GC_UNLOCK();
	return (ret);
}