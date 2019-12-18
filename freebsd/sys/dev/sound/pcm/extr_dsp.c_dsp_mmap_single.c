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
typedef  scalar_t__ vm_size_t ;
typedef  uintptr_t vm_ooffset_t ;
struct vm_object {int dummy; } ;
struct snddev_info {int dummy; } ;
struct pcm_channel {int flags; int /*<<< orphan*/  bufsoft; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int CHN_F_MMAP ; 
 int CHN_F_MMAP_INVALID ; 
 int /*<<< orphan*/  DSP_REGISTERED (struct snddev_info*,struct cdev*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OBJT_DEVICE ; 
 int /*<<< orphan*/  PCM_GIANT_ENTER (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_GIANT_EXIT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_GIANT_LEAVE (struct snddev_info*) ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int SD_F_PRIO_RD ; 
 int SD_F_PRIO_WR ; 
 scalar_t__ SV_ABI_LINUX ; 
 scalar_t__ SV_CURPROC_ABI () ; 
 TYPE_1__* curthread ; 
 struct snddev_info* dsp_get_info (struct cdev*) ; 
 int dsp_mmap_allow_prot_exec ; 
 int /*<<< orphan*/  getchns (struct cdev*,struct pcm_channel**,struct pcm_channel**,int) ; 
 int /*<<< orphan*/  relchns (struct cdev*,struct pcm_channel*,struct pcm_channel*,int) ; 
 scalar_t__ sndbuf_getbufofs (int /*<<< orphan*/ ,uintptr_t) ; 
 scalar_t__ sndbuf_getsize (int /*<<< orphan*/ ) ; 
 struct vm_object* vm_pager_allocate (int /*<<< orphan*/ ,struct cdev*,scalar_t__,int,uintptr_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsp_mmap_single(struct cdev *i_dev, vm_ooffset_t *offset,
    vm_size_t size, struct vm_object **object, int nprot)
{
	struct snddev_info *d;
	struct pcm_channel *wrch, *rdch, *c;

	/*
	 * Reject PROT_EXEC by default. It just doesn't makes sense.
	 * Unfortunately, we have to give up this one due to linux_mmap
	 * changes.
	 *
	 * https://lists.freebsd.org/pipermail/freebsd-emulation/2007-June/003698.html
	 *
	 */
#ifdef SV_ABI_LINUX
	if ((nprot & PROT_EXEC) && (dsp_mmap_allow_prot_exec < 0 ||
	    (dsp_mmap_allow_prot_exec == 0 &&
	    SV_CURPROC_ABI() != SV_ABI_LINUX)))
#else
	if ((nprot & PROT_EXEC) && dsp_mmap_allow_prot_exec < 1)
#endif
		return (EINVAL);

	/*
	 * PROT_READ (alone) selects the input buffer.
	 * PROT_WRITE (alone) selects the output buffer.
	 * PROT_WRITE|PROT_READ together select the output buffer.
	 */
	if ((nprot & (PROT_READ | PROT_WRITE)) == 0)
		return (EINVAL);

	d = dsp_get_info(i_dev);
	if (!DSP_REGISTERED(d, i_dev))
		return (EINVAL);

	PCM_GIANT_ENTER(d);

	getchns(i_dev, &rdch, &wrch, SD_F_PRIO_RD | SD_F_PRIO_WR);

	c = ((nprot & PROT_WRITE) != 0) ? wrch : rdch;
	if (c == NULL || (c->flags & CHN_F_MMAP_INVALID) ||
	    (*offset  + size) > sndbuf_getsize(c->bufsoft) ||
	    (wrch != NULL && (wrch->flags & CHN_F_MMAP_INVALID)) ||
	    (rdch != NULL && (rdch->flags & CHN_F_MMAP_INVALID))) {
		relchns(i_dev, rdch, wrch, SD_F_PRIO_RD | SD_F_PRIO_WR);
		PCM_GIANT_EXIT(d);
		return (EINVAL);
	}

	if (wrch != NULL)
		wrch->flags |= CHN_F_MMAP;
	if (rdch != NULL)
		rdch->flags |= CHN_F_MMAP;

	*offset = (uintptr_t)sndbuf_getbufofs(c->bufsoft, *offset);
	relchns(i_dev, rdch, wrch, SD_F_PRIO_RD | SD_F_PRIO_WR);
	*object = vm_pager_allocate(OBJT_DEVICE, i_dev,
	    size, nprot, *offset, curthread->td_ucred);

	PCM_GIANT_LEAVE(d);

	if (*object == NULL)
		 return (EINVAL);
	return (0);
}