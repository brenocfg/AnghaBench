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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 char* git_path_merge_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void read_merge_msg(struct strbuf *msg)
{
	const char *filename = git_path_merge_msg(the_repository);
	strbuf_reset(msg);
	if (strbuf_read_file(msg, filename, 0) < 0)
		die_errno(_("Could not read from '%s'"), filename);
}