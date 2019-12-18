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
struct bsdtar {int warned_lead_slash; } ;

/* Variables and functions */
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,char const) ; 

__attribute__((used)) static void
warn_strip_leading_char(struct bsdtar *bsdtar, const char *c)
{
	if (!bsdtar->warned_lead_slash) {
		lafe_warnc(0,
			   "Removing leading '%c' from member names",
			   c[0]);
		bsdtar->warned_lead_slash = 1;
	}
}