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
struct fst_session {int dummy; } ;
typedef  enum fst_event_type { ____Placeholder_fst_event_type } fst_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_fst_ctrl_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct fst_session*,union fst_event_extra*) ; 
 int /*<<< orphan*/  on_event ; 

__attribute__((used)) static inline void fst_session_notify_ctrl(struct fst_session *s,
					   enum fst_event_type event_type,
					   union fst_event_extra *extra)
{
	foreach_fst_ctrl_call(on_event, event_type, NULL, s, extra);
}