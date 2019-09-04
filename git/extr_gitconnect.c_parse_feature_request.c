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
 int /*<<< orphan*/  parse_feature_value (char const*,char const*,int /*<<< orphan*/ *) ; 

int parse_feature_request(const char *feature_list, const char *feature)
{
	return !!parse_feature_value(feature_list, feature, NULL);
}