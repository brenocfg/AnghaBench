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
struct commit_graph {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 struct commit_graph* load_commit_graph_one_fd_st (int,struct stat*) ; 
 int open_commit_graph (char const*,int*,struct stat*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct commit_graph *load_commit_graph_one(const char *graph_file)
{

	struct stat st;
	int fd;
	struct commit_graph *g;
	int open_ok = open_commit_graph(graph_file, &fd, &st);

	if (!open_ok)
		return NULL;

	g = load_commit_graph_one_fd_st(fd, &st);

	if (g)
		g->filename = xstrdup(graph_file);

	return g;
}