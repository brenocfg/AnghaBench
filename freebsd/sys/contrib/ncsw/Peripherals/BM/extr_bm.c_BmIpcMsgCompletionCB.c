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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * uint32_t ;
typedef  int /*<<< orphan*/ * t_Handle ;
typedef  int /*<<< orphan*/ * t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blockingFlag ; 

__attribute__((used)) static void BmIpcMsgCompletionCB(t_Handle   h_Module,
                                 uint8_t    *p_Msg,
                                 uint8_t    *p_Reply,
                                 uint32_t   replyLength,
                                 t_Error    status)
{
    SANITY_CHECK_RETURN(h_Module, E_INVALID_HANDLE);

#ifdef DISABLE_SANITY_CHECKS
    UNUSED(h_Module);
#endif /* DISABLE_SANITY_CHECKS */
    UNUSED(p_Msg);UNUSED(p_Reply);UNUSED(replyLength);UNUSED(status);

    blockingFlag = FALSE;
}