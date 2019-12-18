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
struct consdev {int cn_unit; int /*<<< orphan*/  cn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
siocnset(struct consdev *cd, int unit)
{

	cd->cn_unit = unit;
	sprintf(cd->cn_name, "ttyd%d", unit);
}