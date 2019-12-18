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
struct packet_writer {int dummy; } ;
struct object_array {int dummy; } ;
struct commit_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_SHALLOW ; 
 int /*<<< orphan*/  SHALLOW ; 
 int /*<<< orphan*/  disable_commit_graph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_shallow_commits_by_rev_list (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_shallow (struct packet_writer*,struct commit_list*) ; 
 int /*<<< orphan*/  send_unshallow (struct packet_writer*,struct object_array*,struct object_array*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void deepen_by_rev_list(struct packet_writer *writer, int ac,
			       const char **av,
			       struct object_array *shallows,
			       struct object_array *want_obj)
{
	struct commit_list *result;

	disable_commit_graph(the_repository);
	result = get_shallow_commits_by_rev_list(ac, av, SHALLOW, NOT_SHALLOW);
	send_shallow(writer, result);
	free_commit_list(result);
	send_unshallow(writer, shallows, want_obj);
}