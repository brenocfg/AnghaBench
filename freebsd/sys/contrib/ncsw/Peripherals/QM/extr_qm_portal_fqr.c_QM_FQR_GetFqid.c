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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  fqidBase; } ;
typedef  TYPE_1__ t_QmFqr ;
typedef  scalar_t__ t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t QM_FQR_GetFqid(t_Handle h_QmFqr)
{
    t_QmFqr *p_QmFqr = (t_QmFqr *)h_QmFqr;

    SANITY_CHECK_RETURN_VALUE(p_QmFqr, E_INVALID_HANDLE, 0);

    return p_QmFqr->fqidBase;
}