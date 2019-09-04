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
struct strbuf {scalar_t__ len; } ;
typedef  enum commit_msg_cleanup_mode { ____Placeholder_commit_msg_cleanup_mode } commit_msg_cleanup_mode ;

/* Variables and functions */
 int COMMIT_MSG_CLEANUP_NONE ; 
 int rest_is_empty (struct strbuf const*,int /*<<< orphan*/ ) ; 

int message_is_empty(const struct strbuf *sb,
		     enum commit_msg_cleanup_mode cleanup_mode)
{
	if (cleanup_mode == COMMIT_MSG_CLEANUP_NONE && sb->len)
		return 0;
	return rest_is_empty(sb, 0);
}