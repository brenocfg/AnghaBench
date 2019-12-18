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
typedef  int /*<<< orphan*/  time64_t ;
struct carm_msg_sync_time {void* timestamp; void* handle; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct carm_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARM_MSG_MISC ; 
 int /*<<< orphan*/  MISC_SET_TIME ; 
 int /*<<< orphan*/  TAG_ENCODE (unsigned int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memset (struct carm_msg_sync_time*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int carm_fill_sync_time(struct carm_host *host,
					unsigned int idx, void *mem)
{
	struct carm_msg_sync_time *st = mem;

	time64_t tv = ktime_get_real_seconds();

	memset(st, 0, sizeof(*st));
	st->type	= CARM_MSG_MISC;
	st->subtype	= MISC_SET_TIME;
	st->handle	= cpu_to_le32(TAG_ENCODE(idx));
	st->timestamp	= cpu_to_le32(tv);

	return sizeof(struct carm_msg_sync_time);
}