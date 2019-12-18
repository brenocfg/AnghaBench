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

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

__attribute__((used)) static void create_key(const char *prefix, const char *postfix,
		       const char *name, char *buf, int len)
{
	if (prefix && postfix)
		snprintf(buf, len, "%s%s%s", prefix, name, postfix);
	else if (prefix)
		snprintf(buf, len, "%s%s", prefix, name);
	else if (postfix)
		snprintf(buf, len, "%s%s", name, postfix);
	else
		snprintf(buf, len, "%s", name);
}