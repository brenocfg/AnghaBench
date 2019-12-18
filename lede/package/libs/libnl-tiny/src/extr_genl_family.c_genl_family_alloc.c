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
struct genl_family {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  genl_family_ops ; 
 scalar_t__ nl_object_alloc (int /*<<< orphan*/ *) ; 

struct genl_family *genl_family_alloc(void)
{
	return (struct genl_family *) nl_object_alloc(&genl_family_ops);
}