#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t va_buffer_size; int va_mode; int va_initial_mode; scalar_t__ va_buffer; } ;
typedef  TYPE_1__ video_adapter_t ;
struct TYPE_10__ {scalar_t__ sig; int /*<<< orphan*/  regs; } ;
typedef  TYPE_2__ adp_state_t ;
struct TYPE_11__ {int (* load_state ) (TYPE_1__*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  STATE_LOAD ; 
 scalar_t__ VESA_MODE (int) ; 
 scalar_t__ V_STATE_SIG ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_8__* prevvidsw ; 
 int stub1 (TYPE_1__*,void*) ; 
 int stub2 (TYPE_1__*,void*) ; 
 TYPE_1__* vesa_adp ; 
 int /*<<< orphan*/  vesa_bios_post () ; 
 int vesa_bios_save_restore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vesa_set_mode (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * vesa_vmem_buf ; 

__attribute__((used)) static int
vesa_load_state(video_adapter_t *adp, void *p)
{
	void *buf;
	size_t bsize;
	int error, mode;

	if (adp != vesa_adp)
		return ((*prevvidsw->load_state)(adp, p));

	/* Try BIOS POST to restore a sane state. */
	(void)vesa_bios_post();
	bsize = adp->va_buffer_size;
	mode = adp->va_mode;
	error = vesa_set_mode(adp, adp->va_initial_mode);
	if (mode != adp->va_initial_mode)
		error = vesa_set_mode(adp, mode);

	if (vesa_vmem_buf != NULL) {
		if (error == 0 && VESA_MODE(mode)) {
			buf = (void *)adp->va_buffer;
			if (buf != NULL)
				bcopy(vesa_vmem_buf, buf, bsize);
		}
		free(vesa_vmem_buf, M_DEVBUF);
		vesa_vmem_buf = NULL;
	}
	if (((adp_state_t *)p)->sig != V_STATE_SIG)
		return ((*prevvidsw->load_state)(adp, p));
	return (vesa_bios_save_restore(STATE_LOAD, ((adp_state_t *)p)->regs));
}