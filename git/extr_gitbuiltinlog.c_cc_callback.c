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
 int /*<<< orphan*/  extra_cc ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_callback(const struct option *opt, const char *arg, int unset)
{
	if (unset)
		string_list_clear(&extra_cc, 0);
	else
		string_list_append(&extra_cc, arg);
	return 0;
}