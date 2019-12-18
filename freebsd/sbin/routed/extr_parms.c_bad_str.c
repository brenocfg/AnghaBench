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
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static const char *
bad_str(const char *estr)
{
	static char buf[100+8];

	sprintf(buf, "bad \"%.100s\"", estr);
	return buf;
}