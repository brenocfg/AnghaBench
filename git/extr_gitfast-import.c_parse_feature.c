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
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ parse_one_feature (char const*,int) ; 
 scalar_t__ seen_data_command ; 

__attribute__((used)) static void parse_feature(const char *feature)
{
	if (seen_data_command)
		die("Got feature command '%s' after data command", feature);

	if (parse_one_feature(feature, 1))
		return;

	die("This version of fast-import does not support feature %s.", feature);
}