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
 int /*<<< orphan*/  CPP_PARAM ; 
 int /*<<< orphan*/  CPP_S1 ; 
 int /*<<< orphan*/  CPP_S2 ; 
 int /*<<< orphan*/  CPP_S3 ; 
 int /*<<< orphan*/  DECLARE_CPP_MICROSEQ ; 
 int VP0_ECONNECT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpp_microseq ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char,char,char) ; 
 int /*<<< orphan*/  ppb_MS_init_msq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_MS_microseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imm_disconnect(struct vpoio_data *vpo, int *connected, int release_bus)
{
	DECLARE_CPP_MICROSEQ;

	device_t ppbus = device_get_parent(vpo->vpo_dev);
	char s1, s2, s3;
	int ret;

	/* all should be ok */
	if (connected)
		*connected = 0;

	ppb_MS_init_msq(cpp_microseq, 4, CPP_S1, (void *)&s1,
			CPP_S2, (void *)&s2, CPP_S3, (void *)&s3,
			CPP_PARAM, 0x30);

	ppb_MS_microseq(ppbus, vpo->vpo_dev, cpp_microseq, &ret);

	if ((s1 != (char)0xb8 || s2 != (char)0x18 || s3 != (char)0x38)) {
		if (bootverbose)
			device_printf(vpo->vpo_dev,
			    "(disconnect) s1=0x%x s2=0x%x, s3=0x%x\n",
			    s1 & 0xff, s2 & 0xff, s3 & 0xff);
		if (connected)
			*connected = VP0_ECONNECT;
	}

	if (release_bus)
		return (ppb_release_bus(ppbus, vpo->vpo_dev));
	else
		return (0);
}