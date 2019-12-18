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
struct spc {scalar_t__* valp; scalar_t__ val; int /*<<< orphan*/  flags; int /*<<< orphan*/  mylevel; } ;
typedef  scalar_t__ cc_t ;

/* Variables and functions */
 int NSLC ; 
 int /*<<< orphan*/  SLC_NOSUPPORT ; 
 scalar_t__ _POSIX_VDISABLE ; 
 int /*<<< orphan*/  setconnmode (int) ; 
 int /*<<< orphan*/  slc_add_reply (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  slc_end_reply () ; 
 int /*<<< orphan*/  slc_start_reply () ; 
 struct spc* spc_data ; 

void
slc_check(void)
{
    struct spc *spcp;

    slc_start_reply();
    for (spcp = &spc_data[1]; spcp < &spc_data[NSLC+1]; spcp++) {
	if (spcp->valp && spcp->val != *spcp->valp) {
	    spcp->val = *spcp->valp;
	    if (spcp->val == (cc_t)(_POSIX_VDISABLE))
		spcp->flags = SLC_NOSUPPORT;
	    else
		spcp->flags = spcp->mylevel;
	    slc_add_reply(spcp - spc_data, spcp->flags, spcp->val);
	}
    }
    slc_end_reply();
    setconnmode(1);
}