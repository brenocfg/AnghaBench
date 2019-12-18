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
struct attr_check {int dummy; } ;

/* Variables and functions */
 struct attr_check* attr_check_initl (char*,char*,int /*<<< orphan*/ *) ; 
 struct attr_check* merge_attributes ; 

__attribute__((used)) static struct attr_check *load_merge_attributes(void)
{
	if (!merge_attributes)
		merge_attributes = attr_check_initl("merge", "conflict-marker-size", NULL);
	return merge_attributes;
}