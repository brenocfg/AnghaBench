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
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_dev_set_media (struct g_consumer*) ; 
 int /*<<< orphan*/  g_dev_set_physpath (struct g_consumer*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
g_dev_attrchanged(struct g_consumer *cp, const char *attr)
{

	if (strcmp(attr, "GEOM::media") == 0) {
		g_dev_set_media(cp);
		return;
	}

	if (strcmp(attr, "GEOM::physpath") == 0) {
		g_dev_set_physpath(cp);
		return;
	}
}