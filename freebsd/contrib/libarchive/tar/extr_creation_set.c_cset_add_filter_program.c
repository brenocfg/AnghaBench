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
struct creation_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cset_add_filter (struct creation_set*,int,char const*) ; 

void
cset_add_filter_program(struct creation_set *cset, const char *filter)
{
	_cset_add_filter(cset, 1, filter);
}