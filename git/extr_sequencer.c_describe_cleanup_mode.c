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
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUG (char*,int) ; 

__attribute__((used)) static const char *describe_cleanup_mode(int cleanup_mode)
{
	static const char *modes[] = { "whitespace",
				       "verbatim",
				       "scissors",
				       "strip" };

	if (cleanup_mode < ARRAY_SIZE(modes))
		return modes[cleanup_mode];

	BUG("invalid cleanup_mode provided (%d)", cleanup_mode);
}