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
struct call {scalar_t__ cstate; } ;
typedef  enum uni_callstate { ____Placeholder_uni_callstate } uni_callstate ;
typedef  enum call_state { ____Placeholder_call_state } call_state ;

/* Variables and functions */
 scalar_t__ CALLST_N1 ; 
 scalar_t__ CALLST_N3 ; 
 scalar_t__ CALLST_N4 ; 
 scalar_t__ CALLST_N6 ; 
 scalar_t__ CALLST_N7 ; 
 scalar_t__ CALLST_N8 ; 
 scalar_t__ CALLST_N9 ; 
 int CALLST_NULL ; 
 scalar_t__ CALLST_U1 ; 
 scalar_t__ CALLST_U3 ; 
 scalar_t__ CALLST_U4 ; 
 scalar_t__ CALLST_U6 ; 
 scalar_t__ CALLST_U7 ; 
 scalar_t__ CALLST_U8 ; 
 int UNI_CALLSTATE_N1 ; 
 int UNI_CALLSTATE_N3 ; 
 int UNI_CALLSTATE_N4 ; 
 int UNI_CALLSTATE_N6 ; 
 int UNI_CALLSTATE_N7 ; 
 int UNI_CALLSTATE_N8 ; 
 int UNI_CALLSTATE_N9 ; 
 int UNI_CALLSTATE_U1 ; 
 int UNI_CALLSTATE_U3 ; 
 int UNI_CALLSTATE_U4 ; 
 int UNI_CALLSTATE_U6 ; 
 int UNI_CALLSTATE_U7 ; 
 int UNI_CALLSTATE_U8 ; 
 int UNI_CALLSTATE_U9 ; 

__attribute__((used)) static enum call_state
state_compat(struct call *c, enum uni_callstate peer)
{
	if ((c->cstate == CALLST_U1 ||
	     c->cstate == CALLST_U3 ||
	     c->cstate == CALLST_U4) &&
	   (peer == UNI_CALLSTATE_N6 ||
	    peer == UNI_CALLSTATE_N7 ||
	    peer == UNI_CALLSTATE_N8 ||
	    peer == UNI_CALLSTATE_N9))
		return (CALLST_NULL);

	if ((c->cstate == CALLST_N6 ||
	     c->cstate == CALLST_N7 ||
	     c->cstate == CALLST_N8 ||
	     c->cstate == CALLST_N9) &&
	    (peer == UNI_CALLSTATE_U1 ||
	     peer == UNI_CALLSTATE_U3 ||
	     peer == UNI_CALLSTATE_U4))
		return (CALLST_NULL);

	if ((peer == UNI_CALLSTATE_N1 ||
	     peer == UNI_CALLSTATE_N3 ||
	     peer == UNI_CALLSTATE_N4) &&
	   (c->cstate == CALLST_U6 ||
	    c->cstate == CALLST_U7 ||
	    c->cstate == CALLST_U8 ||
	    c->cstate == CALLST_N9))
		return (CALLST_NULL);

	if ((peer == UNI_CALLSTATE_U6 ||
	     peer == UNI_CALLSTATE_U7 ||
	     peer == UNI_CALLSTATE_U8 ||
	     peer == UNI_CALLSTATE_U9) &&
	   (c->cstate == CALLST_N1 ||
	    c->cstate == CALLST_N3 ||
	    c->cstate == CALLST_N4))
		return (CALLST_NULL);

	return (c->cstate);
}