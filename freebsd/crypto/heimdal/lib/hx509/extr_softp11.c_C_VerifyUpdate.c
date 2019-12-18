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
typedef  int /*<<< orphan*/  CK_ULONG ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  int /*<<< orphan*/  CK_RV ;
typedef  int /*<<< orphan*/  CK_BYTE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  VERIFY_SESSION_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_logf (char*) ; 

CK_RV
C_VerifyUpdate(CK_SESSION_HANDLE hSession,
	       CK_BYTE_PTR pPart,
	       CK_ULONG ulPartLen)
{
    INIT_CONTEXT();
    st_logf("VerifyUpdate\n");
    VERIFY_SESSION_HANDLE(hSession, NULL);
    return CKR_FUNCTION_NOT_SUPPORTED;
}