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
struct merge_options {int verbosity; int /*<<< orphan*/  call_depth; } ;

/* Variables and functions */

__attribute__((used)) static int show(struct merge_options *o, int v)
{
	return (!o->call_depth && o->verbosity >= v) || o->verbosity >= 5;
}