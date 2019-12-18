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
struct repository {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int repo_parse_commit_internal (struct repository*,struct commit*,int,int) ; 

int repo_parse_commit_gently(struct repository *r,
			     struct commit *item, int quiet_on_missing)
{
	return repo_parse_commit_internal(r, item, quiet_on_missing, 1);
}