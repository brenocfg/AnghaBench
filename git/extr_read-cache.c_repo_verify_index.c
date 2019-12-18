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
struct repository {int /*<<< orphan*/  index_file; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int verify_index_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int repo_verify_index(struct repository *repo)
{
	return verify_index_from(repo->index, repo->index_file);
}