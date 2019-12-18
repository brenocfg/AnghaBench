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
struct commit {int dummy; } ;
struct check_mergetag_data {int argc; char const** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_one_mergetag ; 
 int for_each_mergetag (int /*<<< orphan*/ ,struct commit*,struct check_mergetag_data*) ; 

__attribute__((used)) static int check_mergetags(struct commit *commit, int argc, const char **argv)
{
	struct check_mergetag_data mergetag_data;

	mergetag_data.argc = argc;
	mergetag_data.argv = argv;
	return for_each_mergetag(check_one_mergetag, commit, &mergetag_data);
}