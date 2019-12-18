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
typedef  union drbd_state {int dummy; } drbd_state ;
struct drbd_connection {scalar_t__ cstate; int /*<<< orphan*/  flags; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_WD_ST_CHG_FAIL ; 
 int /*<<< orphan*/  CONN_WD_ST_CHG_OKAY ; 
 scalar_t__ C_WF_REPORT_PARAMS ; 
 int SS_CW_FAILED_BY_PEER ; 
 int SS_CW_SUCCESS ; 
 int SS_SUCCESS ; 
 int SS_UNKNOWN_ERROR ; 
 int conn_is_valid_transition (struct drbd_connection*,union drbd_state,union drbd_state,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum drbd_state_rv
_conn_rq_cond(struct drbd_connection *connection, union drbd_state mask, union drbd_state val)
{
	enum drbd_state_rv err, rv = SS_UNKNOWN_ERROR; /* continue waiting */;

	if (test_and_clear_bit(CONN_WD_ST_CHG_OKAY, &connection->flags))
		rv = SS_CW_SUCCESS;

	if (test_and_clear_bit(CONN_WD_ST_CHG_FAIL, &connection->flags))
		rv = SS_CW_FAILED_BY_PEER;

	err = conn_is_valid_transition(connection, mask, val, 0);
	if (err == SS_SUCCESS && connection->cstate == C_WF_REPORT_PARAMS)
		return rv;

	return err;
}