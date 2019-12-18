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
struct TYPE_4__ {scalar_t__ _cmp; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int git_vector_search2 (size_t*,TYPE_1__ const*,scalar_t__,void const*) ; 
 scalar_t__ strict_comparison ; 

int git_vector_search(size_t *at_pos, const git_vector *v, const void *entry)
{
	return git_vector_search2(at_pos, v, v->_cmp ? v->_cmp : strict_comparison, entry);
}