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
struct session_state {scalar_t__ session_handle; } ;
struct TYPE_2__ {struct session_state* state; } ;
typedef  scalar_t__ CK_SESSION_HANDLE ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  CKR_SESSION_HANDLE_INVALID ; 
 size_t MAX_NUM_SESSION ; 
 int /*<<< orphan*/  application_error (char*,unsigned long) ; 
 TYPE_1__ soft_token ; 

__attribute__((used)) static CK_RV
verify_session_handle(CK_SESSION_HANDLE hSession,
		      struct session_state **state)
{
    size_t i;

    for (i = 0; i < MAX_NUM_SESSION; i++){
	if (soft_token.state[i].session_handle == hSession)
	    break;
    }
    if (i == MAX_NUM_SESSION) {
	application_error("use of invalid handle: 0x%08lx\n",
			  (unsigned long)hSession);
	return CKR_SESSION_HANDLE_INVALID;
    }
    if (state)
	*state = &soft_token.state[i];
    return CKR_OK;
}