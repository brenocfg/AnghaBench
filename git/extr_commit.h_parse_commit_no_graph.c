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

/* Variables and functions */
 int repo_parse_commit_internal (int /*<<< orphan*/ ,struct commit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static inline int parse_commit_no_graph(struct commit *commit)
{
	return repo_parse_commit_internal(the_repository, commit, 0, 0);
}