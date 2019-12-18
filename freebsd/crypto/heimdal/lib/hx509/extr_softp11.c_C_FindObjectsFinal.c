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
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  VERIFY_SESSION_HANDLE (int /*<<< orphan*/ ,struct session_state**) ; 
 int /*<<< orphan*/  find_object_final (struct session_state*) ; 
 int /*<<< orphan*/  st_logf (char*) ; 

CK_RV
C_FindObjectsFinal(CK_SESSION_HANDLE hSession)
{
    struct session_state *state;

    INIT_CONTEXT();

    st_logf("FindObjectsFinal\n");
    VERIFY_SESSION_HANDLE(hSession, &state);
    find_object_final(state);
    return CKR_OK;
}