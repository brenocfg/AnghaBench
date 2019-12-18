#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ frameAnnotationSize; scalar_t__ frameDataSize; scalar_t__ fqContextSize; int fqContextAddr; } ;
struct TYPE_6__ {TYPE_1__ stashingParams; } ;
typedef  TYPE_2__ t_QmFqrParams ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int /*<<< orphan*/  CACHELINE_SIZE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ QM_CONTEXTA_MAX_STASH_SIZE ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static __inline__ t_Error CheckStashParams(t_QmFqrParams *p_QmFqrParams)
{
    ASSERT_COND(p_QmFqrParams);

    if (p_QmFqrParams->stashingParams.frameAnnotationSize > QM_CONTEXTA_MAX_STASH_SIZE)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Frame Annotation Size Exceeded Max Stash Size(%d)", QM_CONTEXTA_MAX_STASH_SIZE));
    if (p_QmFqrParams->stashingParams.frameDataSize > QM_CONTEXTA_MAX_STASH_SIZE)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Frame Data Size Exceeded Max Stash Size(%d)", QM_CONTEXTA_MAX_STASH_SIZE));
    if (p_QmFqrParams->stashingParams.fqContextSize > QM_CONTEXTA_MAX_STASH_SIZE)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Frame Context Size Exceeded Max Stash Size(%d)", QM_CONTEXTA_MAX_STASH_SIZE));
    if (p_QmFqrParams->stashingParams.fqContextSize)
    {
        if (!p_QmFqrParams->stashingParams.fqContextAddr)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("FQ Context Address Must be givven"));
        if (!IS_ALIGNED(p_QmFqrParams->stashingParams.fqContextAddr, CACHELINE_SIZE))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("FQ Context Address Must be aligned to %d", CACHELINE_SIZE));
        if (p_QmFqrParams->stashingParams.fqContextAddr & 0xffffff0000000000LL)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("FQ Context Address May be up to 40 bit"));
    }

    return E_OK;
}