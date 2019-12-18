#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int glblMaskSize; scalar_t__ parseCode; void* lclMask; int /*<<< orphan*/  maskSupport; scalar_t__ maxNumOfKeys; int /*<<< orphan*/  p_GlblMask; void* glblMaskUpdated; } ;
typedef  TYPE_1__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 scalar_t__ CC_PC_FF_IPDSCP ; 
 scalar_t__ CC_PC_FF_IPTOS_IPV6TC1_IPV6FLOW1 ; 
 scalar_t__ CC_PC_FF_IPTOS_IPV6TC2_IPV6FLOW2 ; 
 scalar_t__ CC_PC_FF_IPV4IPTOS_TC1 ; 
 scalar_t__ CC_PC_FF_IPV4IPTOS_TC2 ; 
 scalar_t__ CC_PC_FF_MPLS1 ; 
 scalar_t__ CC_PC_FF_MPLS_LAST ; 
 scalar_t__ CC_PC_FF_TCI1 ; 
 scalar_t__ CC_PC_FF_TCI2 ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  E_OK ; 
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static t_Error UpdateGblMask(t_FmPcdCcNode *p_CcNode, uint8_t keySize,
                             uint8_t *p_Mask)
{
    uint8_t prvGlblMaskSize = p_CcNode->glblMaskSize;

    if (p_Mask && !p_CcNode->glblMaskUpdated && (keySize <= 4)
            && !p_CcNode->lclMask)
    {
        if (p_CcNode->parseCode && (p_CcNode->parseCode != CC_PC_FF_TCI1)
                && (p_CcNode->parseCode != CC_PC_FF_TCI2)
                && (p_CcNode->parseCode != CC_PC_FF_MPLS1)
                && (p_CcNode->parseCode != CC_PC_FF_MPLS_LAST)
                && (p_CcNode->parseCode != CC_PC_FF_IPV4IPTOS_TC1)
                && (p_CcNode->parseCode != CC_PC_FF_IPV4IPTOS_TC2)
                && (p_CcNode->parseCode != CC_PC_FF_IPTOS_IPV6TC1_IPV6FLOW1)
                && (p_CcNode->parseCode != CC_PC_FF_IPDSCP)
                && (p_CcNode->parseCode != CC_PC_FF_IPTOS_IPV6TC2_IPV6FLOW2))
        {
            p_CcNode->glblMaskSize = 0;
            p_CcNode->lclMask = TRUE;
        }
        else
        {
            memcpy(p_CcNode->p_GlblMask, p_Mask, (sizeof(uint8_t)) * keySize);
            p_CcNode->glblMaskUpdated = TRUE;
            p_CcNode->glblMaskSize = 4;
        }
    }
    else
        if (p_Mask && (keySize <= 4) && !p_CcNode->lclMask)
        {
            if (memcmp(p_CcNode->p_GlblMask, p_Mask, keySize) != 0)
            {
                p_CcNode->lclMask = TRUE;
                p_CcNode->glblMaskSize = 0;
            }
        }
        else
            if (!p_Mask && p_CcNode->glblMaskUpdated && (keySize <= 4))
            {
                uint32_t tmpMask = 0xffffffff;
                if (memcmp(p_CcNode->p_GlblMask, &tmpMask, 4) != 0)
                {
                    p_CcNode->lclMask = TRUE;
                    p_CcNode->glblMaskSize = 0;
                }
            }
            else
                if (p_Mask)
                {
                    p_CcNode->lclMask = TRUE;
                    p_CcNode->glblMaskSize = 0;
                }

    /* In static mode (maxNumOfKeys > 0), local mask is supported
     only is mask support was enabled at initialization */
    if (p_CcNode->maxNumOfKeys && (!p_CcNode->maskSupport) && p_CcNode->lclMask)
    {
        p_CcNode->lclMask = FALSE;
        p_CcNode->glblMaskSize = prvGlblMaskSize;
        return ERROR_CODE(E_NOT_SUPPORTED);
    }

    return E_OK;
}