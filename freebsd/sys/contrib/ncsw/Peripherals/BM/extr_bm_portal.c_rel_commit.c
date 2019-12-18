#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int rcrProd; } ;
typedef  TYPE_1__ t_BmPortal ;

/* Variables and functions */
 int BMAN_RELEASE_FLAG_WAIT_SYNC ; 
 int /*<<< orphan*/  BM_RCR_RING ; 
 int BM_RCR_VERB_BUFCOUNT_MASK ; 
 int BM_RCR_VERB_CMD_BPID_SINGLE ; 
 int /*<<< orphan*/  BmCommit (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  rel_completed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rel_set_thresh (TYPE_1__*,int) ; 

__attribute__((used)) static __inline__ void rel_commit(t_BmPortal *p_BmPortal, uint32_t flags,uint8_t num)
{
    uint32_t rcr_poll;

    BmCommit(p_BmPortal, BM_RCR_RING, (uint8_t)(BM_RCR_VERB_CMD_BPID_SINGLE | (num & BM_RCR_VERB_BUFCOUNT_MASK)));
    /* increment the producer count and capture it for SYNC */
    rcr_poll = ++p_BmPortal->rcrProd;
    if ((flags & BMAN_RELEASE_FLAG_WAIT_SYNC) ==
        BMAN_RELEASE_FLAG_WAIT_SYNC)
        rel_set_thresh(p_BmPortal, 1);
    PUNLOCK(p_BmPortal);
    if ((flags & BMAN_RELEASE_FLAG_WAIT_SYNC) !=
        BMAN_RELEASE_FLAG_WAIT_SYNC)
        return;
    rel_completed(p_BmPortal, rcr_poll);
}