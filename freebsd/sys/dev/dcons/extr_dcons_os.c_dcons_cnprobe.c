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
struct consdev {int /*<<< orphan*/  cn_pri; int /*<<< orphan*/  cn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_NORMAL ; 
 int /*<<< orphan*/  CN_REMOTE ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dcons_cnprobe(struct consdev *cp)
{
	sprintf(cp->cn_name, "dcons");
#if DCONS_FORCE_CONSOLE
	cp->cn_pri = CN_REMOTE;
#else
	cp->cn_pri = CN_NORMAL;
#endif
}