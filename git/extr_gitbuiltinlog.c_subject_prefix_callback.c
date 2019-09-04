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
struct rev_info {char const* subject_prefix; } ;
struct option {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int subject_prefix ; 

__attribute__((used)) static int subject_prefix_callback(const struct option *opt, const char *arg,
			    int unset)
{
	BUG_ON_OPT_NEG(unset);
	subject_prefix = 1;
	((struct rev_info *)opt->value)->subject_prefix = arg;
	return 0;
}