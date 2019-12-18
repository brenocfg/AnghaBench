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
 char* AJU_TTYNAME ; 
 int /*<<< orphan*/  CN_NORMAL ; 
 int /*<<< orphan*/  CN_REMOTE ; 
 int RB_SERIAL ; 
 int boothowto ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aju_cnprobe(struct consdev *cp)
{

	sprintf(cp->cn_name, "%s%d", AJU_TTYNAME, 0);
	cp->cn_pri = (boothowto & RB_SERIAL) ? CN_REMOTE : CN_NORMAL;
}