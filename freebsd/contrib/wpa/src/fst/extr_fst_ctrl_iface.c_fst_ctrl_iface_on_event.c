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
typedef  union fst_event_extra {int dummy; } fst_event_extra ;
typedef  int /*<<< orphan*/  u32 ;
struct fst_session {int dummy; } ;
struct fst_iface {int dummy; } ;
typedef  enum fst_event_type { ____Placeholder_fst_event_type } fst_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  FST_INVALID_SESSION_ID ; 
 int /*<<< orphan*/  fst_ctrl_iface_notify (struct fst_iface*,int /*<<< orphan*/ ,int,union fst_event_extra const*) ; 
 int /*<<< orphan*/  fst_session_get_id (struct fst_session*) ; 

__attribute__((used)) static void fst_ctrl_iface_on_event(enum fst_event_type event_type,
				    struct fst_iface *i, struct fst_session *s,
				    const union fst_event_extra *extra)
{
	u32 session_id = s ? fst_session_get_id(s) : FST_INVALID_SESSION_ID;

	fst_ctrl_iface_notify(i, session_id, event_type, extra);
}