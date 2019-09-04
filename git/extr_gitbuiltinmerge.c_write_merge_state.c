#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct commit_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_path_merge_msg (int /*<<< orphan*/ ) ; 
 TYPE_1__ merge_msg ; 
 int /*<<< orphan*/  strbuf_addch (TYPE_1__*,char) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_file_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_merge_heads (struct commit_list*) ; 

__attribute__((used)) static void write_merge_state(struct commit_list *remoteheads)
{
	write_merge_heads(remoteheads);
	strbuf_addch(&merge_msg, '\n');
	write_file_buf(git_path_merge_msg(the_repository), merge_msg.buf,
		       merge_msg.len);
}