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
typedef  scalar_t__ uid_t ;
struct ClearToken {scalar_t__ EndTimestamp; scalar_t__ BeginTimestamp; } ;

/* Variables and functions */
 scalar_t__ ODD (scalar_t__) ; 

void
_kafs_fixup_viceid(struct ClearToken *ct, uid_t uid)
{
#define ODD(x) ((x) & 1)
    /* According to Transarc conventions ViceId is valid iff
     * (EndTimestamp - BeginTimestamp) is odd. By decrementing EndTime
     * the transformations:
     *
     * (issue_date, life) -> (StartTime, EndTime) -> (issue_date, life)
     * preserves the original values.
     */
    if (uid != 0)		/* valid ViceId */
    {
	if (!ODD(ct->EndTimestamp - ct->BeginTimestamp))
	    ct->EndTimestamp--;
    }
    else			/* not valid ViceId */
    {
	if (ODD(ct->EndTimestamp - ct->BeginTimestamp))
	    ct->EndTimestamp--;
    }
}