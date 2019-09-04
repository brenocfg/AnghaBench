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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int git_open (char const*) ; 

int open_commit_graph(const char *graph_file, int *fd, struct stat *st)
{
	*fd = git_open(graph_file);
	if (*fd < 0)
		return 0;
	if (fstat(*fd, st)) {
		close(*fd);
		return 0;
	}
	return 1;
}