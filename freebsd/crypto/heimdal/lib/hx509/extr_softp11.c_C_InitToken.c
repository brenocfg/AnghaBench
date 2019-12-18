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
typedef  int /*<<< orphan*/  CK_UTF8CHAR_PTR ;
typedef  int /*<<< orphan*/  CK_ULONG ;
typedef  scalar_t__ CK_SLOT_ID ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  st_logf (char*,int) ; 

CK_RV
C_InitToken(CK_SLOT_ID slotID,
	    CK_UTF8CHAR_PTR pPin,
	    CK_ULONG ulPinLen,
	    CK_UTF8CHAR_PTR pLabel)
{
    INIT_CONTEXT();
    st_logf("InitToken: slot %d\n", (int)slotID);
    return CKR_FUNCTION_NOT_SUPPORTED;
}