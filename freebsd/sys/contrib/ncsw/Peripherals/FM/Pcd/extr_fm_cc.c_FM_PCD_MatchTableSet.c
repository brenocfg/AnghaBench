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
typedef  int /*<<< orphan*/ * t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdCcNodeParams ;
typedef  int /*<<< orphan*/  t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
#define  E_BUSY 129 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
#define  E_OK 128 
 int GET_ERROR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MatchTableSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

t_Handle FM_PCD_MatchTableSet(t_Handle h_FmPcd,
                              t_FmPcdCcNodeParams *p_CcNodeParam)
{
    t_FmPcdCcNode *p_CcNode;
    t_Error err;

    SANITY_CHECK_RETURN_VALUE(h_FmPcd, E_INVALID_HANDLE, NULL);
    SANITY_CHECK_RETURN_VALUE(p_CcNodeParam, E_NULL_POINTER, NULL);

    p_CcNode = (t_FmPcdCcNode*)XX_Malloc(sizeof(t_FmPcdCcNode));
    if (!p_CcNode)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("No memory"));
        return NULL;
    }
    memset(p_CcNode, 0, sizeof(t_FmPcdCcNode));

    err = MatchTableSet(h_FmPcd, p_CcNode, p_CcNodeParam);

    switch(GET_ERROR_TYPE(err)
)    {
        case E_OK:
        break;

        case E_BUSY:
        DBG(TRACE, ("E_BUSY error"));
        return NULL;

        default:
        REPORT_ERROR(MAJOR, err, NO_MSG);
        return NULL;
    }

    return p_CcNode;
}