#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* next_name ) (char const**,TYPE_1__*) ;} ;
typedef  TYPE_1__ git_reference_iterator ;

/* Variables and functions */
 int stub1 (char const**,TYPE_1__*) ; 

int git_refdb_iterator_next_name(const char **out, git_reference_iterator *iter)
{
	return iter->next_name(out, iter);
}