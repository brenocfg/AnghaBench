#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct merge_msg_entry {TYPE_1__* merge_head; } ;
struct TYPE_6__ {scalar_t__ length; scalar_t__* contents; } ;
typedef  TYPE_2__ git_vector ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_5__ {char* remote_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int merge_msg_write_entries (int /*<<< orphan*/ *,TYPE_2__*,char*,char*,int /*<<< orphan*/ ,char const*,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merge_msg_write_remotes(
	git_filebuf *file,
	git_vector *entries,
	char sep)
{
	const char *source;

	if (entries->length == 0)
		return 0;

	source = ((struct merge_msg_entry *)entries->contents[0])->merge_head->remote_url;

	return merge_msg_write_entries(file, entries,
		"branch", "branches", strlen(GIT_REFS_HEADS_DIR), source, sep);
}