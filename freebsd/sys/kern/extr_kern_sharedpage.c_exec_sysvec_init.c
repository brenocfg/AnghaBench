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
struct sysentvec {int sv_flags; scalar_t__ sv_shared_page_base; scalar_t__ sv_timekeep_base; int /*<<< orphan*/  sv_sigcode; int /*<<< orphan*/ * sv_szsigcode; scalar_t__ sv_sigcode_base; int /*<<< orphan*/  sv_shared_page_obj; } ;
struct TYPE_6__ {scalar_t__ sv_timekeep_off; } ;
struct TYPE_5__ {scalar_t__ sv_timekeep_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int SV_ABI_FREEBSD ; 
 int SV_ABI_MASK ; 
 int SV_ILP32 ; 
 int SV_SHP ; 
 int SV_TIMEKEEP ; 
 TYPE_1__* alloc_sv_tk () ; 
 TYPE_2__* alloc_sv_tk_compat32 () ; 
 TYPE_2__* compat32_svtk ; 
 TYPE_1__* host_svtk ; 
 scalar_t__ shared_page_fill (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_page_obj ; 

void
exec_sysvec_init(void *param)
{
	struct sysentvec *sv;

	sv = (struct sysentvec *)param;
	if ((sv->sv_flags & SV_SHP) == 0)
		return;
	sv->sv_shared_page_obj = shared_page_obj;
	sv->sv_sigcode_base = sv->sv_shared_page_base +
	    shared_page_fill(*(sv->sv_szsigcode), 16, sv->sv_sigcode);
	if ((sv->sv_flags & SV_ABI_MASK) != SV_ABI_FREEBSD)
		return;
	if ((sv->sv_flags & SV_TIMEKEEP) != 0) {
#ifdef COMPAT_FREEBSD32
		if ((sv->sv_flags & SV_ILP32) != 0) {
			KASSERT(compat32_svtk == NULL,
			    ("Compat32 already registered"));
			compat32_svtk = alloc_sv_tk_compat32();
			sv->sv_timekeep_base = sv->sv_shared_page_base +
			    compat32_svtk->sv_timekeep_off;
		} else {
#endif
			KASSERT(host_svtk == NULL, ("Host already registered"));
			host_svtk = alloc_sv_tk();
			sv->sv_timekeep_base = sv->sv_shared_page_base +
			    host_svtk->sv_timekeep_off;
#ifdef COMPAT_FREEBSD32
		}
#endif
	}
}