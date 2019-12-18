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
struct vpoio_data {int /*<<< orphan*/  vpo_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_MICROSEQUENCE ; 
 int /*<<< orphan*/  PPB_INTR ; 
 int /*<<< orphan*/  WAIT_RET ; 
 int /*<<< orphan*/  WAIT_TMO ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nBUSY ; 
 int /*<<< orphan*/  ppb_MS_init_msq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ppb_poll_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_microseq ; 

__attribute__((used)) static char
vpoio_wait(struct vpoio_data *vpo, int tmo)
{
	DECLARE_WAIT_MICROSEQUENCE;

	device_t ppbus = device_get_parent(vpo->vpo_dev);
	int ret, err;

#if 0	/* broken */
	if (ppb_poll_device(ppbus, 150, nBUSY, nBUSY, PPB_INTR))
		return (0);

	return (ppb_rstr(ppbus) & 0xf0);
#endif

	/*
	 * Return some status information.
	 * Semantics :	0xc0 = ZIP wants more data
	 *		0xd0 = ZIP wants to send more data
	 *		0xe0 = ZIP wants command
	 *		0xf0 = end of transfer, ZIP is sending status
	 */

	ppb_MS_init_msq(wait_microseq, 2,
			WAIT_RET, (void *)&ret,
			WAIT_TMO, tmo);

	ppb_MS_microseq(ppbus, vpo->vpo_dev, wait_microseq, &err);

	if (err)
		return (0);	 /* command timed out */

	return(ret);
}