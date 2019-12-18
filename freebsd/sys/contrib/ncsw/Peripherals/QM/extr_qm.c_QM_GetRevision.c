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
typedef  int /*<<< orphan*/  t_QmRevisionInfo ;
typedef  int /*<<< orphan*/  t_Qm ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 int /*<<< orphan*/  QmGetRevision (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

t_Error QM_GetRevision(t_Handle h_Qm, t_QmRevisionInfo *p_QmRevisionInfo)
{
    t_Qm        *p_Qm = (t_Qm*)h_Qm;

    SANITY_CHECK_RETURN_ERROR(p_Qm, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_QmRevisionInfo, E_NULL_POINTER);

    return QmGetRevision(p_Qm, p_QmRevisionInfo);
}