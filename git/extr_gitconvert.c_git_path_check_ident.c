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
struct attr_check_item {char* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_TRUE (char const*) ; 

__attribute__((used)) static int git_path_check_ident(struct attr_check_item *check)
{
	const char *value = check->value;

	return !!ATTR_TRUE(value);
}