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
struct rev_info {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int for_each_mergetag (int /*<<< orphan*/ ,struct commit*,struct rev_info*) ; 
 int /*<<< orphan*/  show_one_mergetag ; 

__attribute__((used)) static int show_mergetag(struct rev_info *opt, struct commit *commit)
{
	return for_each_mergetag(show_one_mergetag, commit, opt);
}