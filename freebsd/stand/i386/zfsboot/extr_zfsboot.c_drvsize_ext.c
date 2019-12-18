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
typedef  int uint64_t ;
struct dsk {int drive; } ;
struct zfsdsk {struct dsk dsk; } ;
struct TYPE_2__ {int addr; int eax; int edx; int ecx; int ebx; int /*<<< orphan*/  efl; void* ctl; } ;

/* Variables and functions */
 int EDD_INTERFACE_FIXED_DISK ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 void* V86_FLAGS ; 
 int drvsize (struct dsk*) ; 
 int drvsize_gpt (struct dsk*) ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static uint64_t
drvsize_ext(struct zfsdsk *zdsk)
{
	struct dsk *dskp;
	uint64_t size, tmp;
	int cyl, hds, sec;

	dskp = &zdsk->dsk;

	/* Try to read disk size from GPT */
	size = drvsize_gpt(dskp);
	if (size != 0)
		return (size);

	v86.ctl = V86_FLAGS;
	v86.addr = 0x13;
	v86.eax = 0x800;
	v86.edx = dskp->drive;
	v86int();

	/* Don't error out if we get bad sector number, try EDD as well */
	if (V86_CY(v86.efl) ||	/* carry set */
	    (v86.edx & 0xff) <= (unsigned)(dskp->drive & 0x7f)) /* unit # bad */
		return (0);
	cyl = ((v86.ecx & 0xc0) << 2) + ((v86.ecx & 0xff00) >> 8) + 1;
	/* Convert max head # -> # of heads */
	hds = ((v86.edx & 0xff00) >> 8) + 1;
	sec = v86.ecx & 0x3f;

	size = (uint64_t)cyl * hds * sec;

	/* Determine if we can use EDD with this device. */
	v86.ctl = V86_FLAGS;
	v86.addr = 0x13;
	v86.eax = 0x4100;
	v86.edx = dskp->drive;
	v86.ebx = 0x55aa;
	v86int();
	if (V86_CY(v86.efl) ||  /* carry set */
	    (v86.ebx & 0xffff) != 0xaa55 || /* signature */
	    (v86.ecx & EDD_INTERFACE_FIXED_DISK) == 0)
		return (size);

	tmp = drvsize(dskp);
	if (tmp > size)
		size = tmp;

	return (size);
}