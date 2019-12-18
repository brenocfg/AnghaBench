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
struct session_state {int dummy; } ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  scalar_t__ CK_RV ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  application_error (char*) ; 
 int /*<<< orphan*/  close_session (struct session_state*) ; 
 int /*<<< orphan*/  st_logf (char*) ; 
 scalar_t__ verify_session_handle (int /*<<< orphan*/ ,struct session_state**) ; 

CK_RV
C_CloseSession(CK_SESSION_HANDLE hSession)
{
    struct session_state *state;
    INIT_CONTEXT();
    st_logf("CloseSession\n");

    if (verify_session_handle(hSession, &state) != CKR_OK)
	application_error("closed session not open");
    else
	close_session(state);

    return CKR_OK;
}