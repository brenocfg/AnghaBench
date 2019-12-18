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
typedef  int /*<<< orphan*/  td ;
struct fst_tear_down {int /*<<< orphan*/  fsts_id; int /*<<< orphan*/  action; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsts_id; int /*<<< orphan*/ * new_iface; int /*<<< orphan*/ * old_iface; } ;
struct fst_session {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FST_ACTION_TEAR_DOWN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_printf_session (struct fst_session*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fst_printf_sframe (struct fst_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fst_session_is_in_progress (struct fst_session*) ; 
 int fst_session_send_action (struct fst_session*,int /*<<< orphan*/ ,struct fst_tear_down*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct fst_tear_down*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fst_session_send_tear_down(struct fst_session *s)
{
	struct fst_tear_down td;
	int res;

	if (!fst_session_is_in_progress(s)) {
		fst_printf_session(s, MSG_ERROR, "No FST setup to tear down");
		return -1;
	}

	WPA_ASSERT(s->data.old_iface != NULL);
	WPA_ASSERT(s->data.new_iface != NULL);

	os_memset(&td, 0, sizeof(td));

	td.action = FST_ACTION_TEAR_DOWN;
	td.fsts_id = host_to_le32(s->data.fsts_id);

	res = fst_session_send_action(s, TRUE, &td, sizeof(td), NULL);
	if (!res)
		fst_printf_sframe(s, TRUE, MSG_INFO, "FST TearDown sent");
	else
		fst_printf_sframe(s, TRUE, MSG_ERROR,
				  "failed to send FST TearDown");

	return res;
}