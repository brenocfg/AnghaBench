#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ login_done; } ;
struct TYPE_8__ {TYPE_1__ flags; } ;
struct TYPE_7__ {int slotID; scalar_t__ ulDeviceError; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__* CK_SESSION_INFO_PTR ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKF_SERIAL_SESSION ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  CKS_RO_PUBLIC_SESSION ; 
 int /*<<< orphan*/  CKS_RO_USER_FUNCTIONS ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  VERIFY_SESSION_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 TYPE_3__ soft_token ; 
 int /*<<< orphan*/  st_logf (char*) ; 

CK_RV
C_GetSessionInfo(CK_SESSION_HANDLE hSession,
		 CK_SESSION_INFO_PTR pInfo)
{
    st_logf("GetSessionInfo\n");
    INIT_CONTEXT();

    VERIFY_SESSION_HANDLE(hSession, NULL);

    memset(pInfo, 20, sizeof(*pInfo));

    pInfo->slotID = 1;
    if (soft_token.flags.login_done)
	pInfo->state = CKS_RO_USER_FUNCTIONS;
    else
	pInfo->state = CKS_RO_PUBLIC_SESSION;
    pInfo->flags = CKF_SERIAL_SESSION;
    pInfo->ulDeviceError = 0;

    return CKR_OK;
}