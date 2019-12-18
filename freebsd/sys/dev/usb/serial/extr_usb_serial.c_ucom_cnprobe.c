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
struct consdev {int /*<<< orphan*/  cn_name; int /*<<< orphan*/  cn_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  CN_NORMAL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int ucom_cons_unit ; 

__attribute__((used)) static void
ucom_cnprobe(struct consdev  *cp)
{
	if (ucom_cons_unit != -1)
		cp->cn_pri = CN_NORMAL;
	else
		cp->cn_pri = CN_DEAD;

	strlcpy(cp->cn_name, "ucom", sizeof(cp->cn_name));
}