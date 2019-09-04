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
struct mailinfo {int filter_stage; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_commit_msg (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  handle_patch (struct mailinfo*,struct strbuf*) ; 

__attribute__((used)) static void handle_filter(struct mailinfo *mi, struct strbuf *line)
{
	switch (mi->filter_stage) {
	case 0:
		if (!handle_commit_msg(mi, line))
			break;
		mi->filter_stage++;
		/* fallthrough */
	case 1:
		handle_patch(mi, line);
		break;
	}
}