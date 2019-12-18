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
 int /*<<< orphan*/  free (struct regdata*) ; 
 int /*<<< orphan*/  lib80211_regdomain_cleanup (struct regdata*) ; 

void
lib80211_free_regdata(struct regdata *rdp)
{
	lib80211_regdomain_cleanup(rdp);
	free(rdp);
}