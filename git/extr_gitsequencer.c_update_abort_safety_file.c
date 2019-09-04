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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  git_path_abort_safety_file () ; 
 int /*<<< orphan*/  git_path_seq_dir () ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void update_abort_safety_file(void)
{
	struct object_id head;

	/* Do nothing on a single-pick */
	if (!file_exists(git_path_seq_dir()))
		return;

	if (!get_oid("HEAD", &head))
		write_file(git_path_abort_safety_file(), "%s", oid_to_hex(&head));
	else
		write_file(git_path_abort_safety_file(), "%s", "");
}