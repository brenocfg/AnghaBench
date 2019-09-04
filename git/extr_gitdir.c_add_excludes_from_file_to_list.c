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
struct index_state {int dummy; } ;
struct exclude_list {int dummy; } ;

/* Variables and functions */
 int add_excludes (char const*,char const*,int,struct exclude_list*,struct index_state*,int /*<<< orphan*/ *) ; 

int add_excludes_from_file_to_list(const char *fname, const char *base,
				   int baselen, struct exclude_list *el,
				   struct index_state *istate)
{
	return add_excludes(fname, base, baselen, el, istate, NULL);
}