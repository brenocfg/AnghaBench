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
struct commit_graft {int nr_parent; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_buf_write (struct strbuf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advertise_shallow_grafts_cb(const struct commit_graft *graft, void *cb)
{
	struct strbuf *sb = cb;
	if (graft->nr_parent == -1)
		packet_buf_write(sb, "shallow %s\n", oid_to_hex(&graft->oid));
	return 0;
}