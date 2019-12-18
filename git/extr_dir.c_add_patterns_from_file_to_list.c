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
struct pattern_list {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int add_patterns (char const*,char const*,int,struct pattern_list*,struct index_state*,int /*<<< orphan*/ *) ; 

int add_patterns_from_file_to_list(const char *fname, const char *base,
				   int baselen, struct pattern_list *pl,
				   struct index_state *istate)
{
	return add_patterns(fname, base, baselen, pl, istate, NULL);
}