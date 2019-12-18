#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct option {scalar_t__ value; } ;
struct TYPE_2__ {int called; char const* arg; int unset; } ;

/* Variables and functions */
 TYPE_1__ length_cb ; 
 int strlen (char const*) ; 

__attribute__((used)) static int length_callback(const struct option *opt, const char *arg, int unset)
{
	length_cb.called = 1;
	length_cb.arg = arg;
	length_cb.unset = unset;

	if (unset)
		return 1; /* do not support unset */

	*(int *)opt->value = strlen(arg);
	return 0;
}