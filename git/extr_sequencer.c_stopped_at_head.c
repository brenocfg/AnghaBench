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
struct object_id {int dummy; } ;
struct commit_message {char* label; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_message (struct commit*,struct commit_message*) ; 
 scalar_t__ get_message (struct commit*,struct commit_message*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 struct commit* lookup_commit (struct repository*,struct object_id*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int stopped_at_head(struct repository *r)
{
	struct object_id head;
	struct commit *commit;
	struct commit_message message;

	if (get_oid("HEAD", &head) ||
	    !(commit = lookup_commit(r, &head)) ||
	    parse_commit(commit) || get_message(commit, &message))
		fprintf(stderr, _("Stopped at HEAD\n"));
	else {
		fprintf(stderr, _("Stopped at %s\n"), message.label);
		free_message(commit, &message);
	}
	return 0;

}