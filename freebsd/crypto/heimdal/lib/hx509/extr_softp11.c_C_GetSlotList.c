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
typedef  int* CK_ULONG_PTR ;
typedef  int* CK_SLOT_ID_PTR ;
typedef  int /*<<< orphan*/  CK_RV ;
typedef  scalar_t__ CK_BBOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  st_logf (char*,char*) ; 

CK_RV
C_GetSlotList(CK_BBOOL tokenPresent,
	      CK_SLOT_ID_PTR pSlotList,
	      CK_ULONG_PTR   pulCount)
{
    INIT_CONTEXT();
    st_logf("GetSlotList: %s\n",
	    tokenPresent ? "tokenPresent" : "token not Present");
    if (pSlotList)
	pSlotList[0] = 1;
    *pulCount = 1;
    return CKR_OK;
}