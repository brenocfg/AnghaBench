#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct aioliojob* p_lio; } ;
struct knote {TYPE_1__ kn_ptr; } ;
struct aioliojob {int lioj_flags; } ;

/* Variables and functions */
 int LIOJ_KEVENT_POSTED ; 

__attribute__((used)) static int
filt_lio(struct knote *kn, long hint)
{
	struct aioliojob * lj = kn->kn_ptr.p_lio;

	return (lj->lioj_flags & LIOJ_KEVENT_POSTED);
}