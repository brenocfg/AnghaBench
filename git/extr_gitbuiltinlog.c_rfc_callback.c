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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int subject_prefix_callback (struct option const*,char*,int) ; 

__attribute__((used)) static int rfc_callback(const struct option *opt, const char *arg, int unset)
{
	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	return subject_prefix_callback(opt, "RFC PATCH", unset);
}