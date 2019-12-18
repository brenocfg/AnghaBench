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
struct regdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct regdata* lib80211_alloc_regdata () ; 

__attribute__((used)) static struct regdata *
getregdata(void)
{
	static struct regdata *rdp = NULL;
	if (rdp == NULL) {
		rdp = lib80211_alloc_regdata();
		if (rdp == NULL)
			errx(-1, "missing or corrupted regdomain database");
	}
	return rdp;
}