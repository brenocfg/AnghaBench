#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct reflog_walk_info {struct commit_reflog* last_commit_reflog; } ;
struct reflog_info {int /*<<< orphan*/  message; } ;
struct commit_reflog {int recno; TYPE_1__* reflogs; } ;
struct TYPE_2__ {struct reflog_info* items; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

void get_reflog_message(struct strbuf *sb,
			struct reflog_walk_info *reflog_info)
{
	struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
	struct reflog_info *info;
	size_t len;

	if (!commit_reflog)
		return;

	info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
	len = strlen(info->message);
	if (len > 0)
		len--; /* strip away trailing newline */
	strbuf_add(sb, info->message, len);
}