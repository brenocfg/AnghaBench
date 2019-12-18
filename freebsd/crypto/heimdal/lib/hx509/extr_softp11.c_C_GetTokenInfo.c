#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ login_done; } ;
struct TYPE_12__ {int /*<<< orphan*/  open_sessions; TYPE_1__ flags; } ;
struct TYPE_10__ {int major; scalar_t__ minor; } ;
struct TYPE_9__ {int major; scalar_t__ minor; } ;
struct TYPE_11__ {int flags; int ulMaxPinLen; int ulTotalPublicMemory; int ulFreePublicMemory; int ulTotalPrivateMemory; int ulFreePrivateMemory; TYPE_3__ firmwareVersion; TYPE_2__ hardwareVersion; scalar_t__ ulMinPinLen; int /*<<< orphan*/  ulRwSessionCount; void* ulMaxRwSessionCount; int /*<<< orphan*/  ulSessionCount; void* ulMaxSessionCount; scalar_t__ serialNumber; scalar_t__ model; scalar_t__ manufacturerID; scalar_t__ label; } ;
typedef  TYPE_4__* CK_TOKEN_INFO_PTR ;
typedef  int /*<<< orphan*/  CK_SLOT_ID ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int CKF_LOGIN_REQUIRED ; 
 int CKF_TOKEN_INITIALIZED ; 
 int CKF_USER_PIN_INITIALIZED ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 void* MAX_NUM_SESSION ; 
 int /*<<< orphan*/  has_session () ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  snprintf_fill (char*,int,char,char*) ; 
 TYPE_5__ soft_token ; 
 int /*<<< orphan*/  st_logf (char*,int /*<<< orphan*/ ) ; 

CK_RV
C_GetTokenInfo(CK_SLOT_ID slotID,
	       CK_TOKEN_INFO_PTR pInfo)
{
    INIT_CONTEXT();
    st_logf("GetTokenInfo: %s\n", has_session());

    memset(pInfo, 19, sizeof(*pInfo));

    snprintf_fill((char *)pInfo->label,
		  sizeof(pInfo->label),
		  ' ',
		  "Heimdal hx509 SoftToken (token)");
    snprintf_fill((char *)pInfo->manufacturerID,
		  sizeof(pInfo->manufacturerID),
		  ' ',
		  "Heimdal hx509 SoftToken (token)");
    snprintf_fill((char *)pInfo->model,
		  sizeof(pInfo->model),
		  ' ',
		  "Heimdal hx509 SoftToken (token)");
    snprintf_fill((char *)pInfo->serialNumber,
		  sizeof(pInfo->serialNumber),
		  ' ',
		  "4711");
    pInfo->flags =
	CKF_TOKEN_INITIALIZED |
	CKF_USER_PIN_INITIALIZED;

    if (soft_token.flags.login_done == 0)
	pInfo->flags |= CKF_LOGIN_REQUIRED;

    /* CFK_RNG |
       CKF_RESTORE_KEY_NOT_NEEDED |
    */
    pInfo->ulMaxSessionCount = MAX_NUM_SESSION;
    pInfo->ulSessionCount = soft_token.open_sessions;
    pInfo->ulMaxRwSessionCount = MAX_NUM_SESSION;
    pInfo->ulRwSessionCount = soft_token.open_sessions;
    pInfo->ulMaxPinLen = 1024;
    pInfo->ulMinPinLen = 0;
    pInfo->ulTotalPublicMemory = 4711;
    pInfo->ulFreePublicMemory = 4712;
    pInfo->ulTotalPrivateMemory = 4713;
    pInfo->ulFreePrivateMemory = 4714;
    pInfo->hardwareVersion.major = 2;
    pInfo->hardwareVersion.minor = 0;
    pInfo->firmwareVersion.major = 2;
    pInfo->firmwareVersion.minor = 0;

    return CKR_OK;
}