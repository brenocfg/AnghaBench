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
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;

/* Variables and functions */
 int C_CONNECTED ; 
 int C_DISCONNECTING ; 
 int C_STANDALONE ; 
 int C_TEAR_DOWN ; 
 int C_TIMEOUT ; 
 int C_UNCONNECTED ; 
 int C_WF_REPORT_PARAMS ; 
 int SS_ALREADY_STANDALONE ; 
 int SS_IN_TRANSIENT_STATE ; 
 int SS_NEED_CONNECTION ; 
 int SS_NOTHING_TO_DO ; 
 int SS_SUCCESS ; 

__attribute__((used)) static enum drbd_state_rv
is_valid_conn_transition(enum drbd_conns oc, enum drbd_conns nc)
{
	/* no change -> nothing to do, at least for the connection part */
	if (oc == nc)
		return SS_NOTHING_TO_DO;

	/* disconnect of an unconfigured connection does not make sense */
	if (oc == C_STANDALONE && nc == C_DISCONNECTING)
		return SS_ALREADY_STANDALONE;

	/* from C_STANDALONE, we start with C_UNCONNECTED */
	if (oc == C_STANDALONE && nc != C_UNCONNECTED)
		return SS_NEED_CONNECTION;

	/* When establishing a connection we need to go through WF_REPORT_PARAMS!
	   Necessary to do the right thing upon invalidate-remote on a disconnected resource */
	if (oc < C_WF_REPORT_PARAMS && nc >= C_CONNECTED)
		return SS_NEED_CONNECTION;

	/* After a network error only C_UNCONNECTED or C_DISCONNECTING may follow. */
	if (oc >= C_TIMEOUT && oc <= C_TEAR_DOWN && nc != C_UNCONNECTED && nc != C_DISCONNECTING)
		return SS_IN_TRANSIENT_STATE;

	/* After C_DISCONNECTING only C_STANDALONE may follow */
	if (oc == C_DISCONNECTING && nc != C_STANDALONE)
		return SS_IN_TRANSIENT_STATE;

	return SS_SUCCESS;
}