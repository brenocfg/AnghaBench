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

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int file_exists (char const*) ; 
 struct repository* the_repository ; 

int repo_file_exists(struct repository *repo, const char *path)
{
	if (repo != the_repository)
		BUG("do not know how to check file existence in arbitrary repo");

	return file_exists(path);
}