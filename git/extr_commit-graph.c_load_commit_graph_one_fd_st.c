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
struct stat {int /*<<< orphan*/  st_size; } ;
struct commit_graph {int dummy; } ;

/* Variables and functions */
 size_t GRAPH_MIN_SIZE ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 struct commit_graph* parse_commit_graph (void*,int,size_t) ; 
 void* xmmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t xsize_t (int /*<<< orphan*/ ) ; 

struct commit_graph *load_commit_graph_one_fd_st(int fd, struct stat *st)
{
	void *graph_map;
	size_t graph_size;
	struct commit_graph *ret;

	graph_size = xsize_t(st->st_size);

	if (graph_size < GRAPH_MIN_SIZE) {
		close(fd);
		error(_("commit-graph file is too small"));
		return NULL;
	}
	graph_map = xmmap(NULL, graph_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ret = parse_commit_graph(graph_map, fd, graph_size);

	if (!ret) {
		munmap(graph_map, graph_size);
		close(fd);
	}

	return ret;
}