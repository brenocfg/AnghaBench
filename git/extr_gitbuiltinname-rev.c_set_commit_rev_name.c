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
struct rev_name {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct rev_name** commit_rev_name_at (int /*<<< orphan*/ *,struct commit*) ; 
 int /*<<< orphan*/  rev_names ; 

__attribute__((used)) static void set_commit_rev_name(struct commit *commit, struct rev_name *name)
{
	*commit_rev_name_at(&rev_names, commit) = name;
}