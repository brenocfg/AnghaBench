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
typedef  int /*<<< orphan*/  t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  BmPoolFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

t_Error BM_POOL_Free(t_Handle h_BmPool)
{
    SANITY_CHECK_RETURN_ERROR(h_BmPool, E_INVALID_HANDLE);

    return BmPoolFree(h_BmPool, FALSE);
}