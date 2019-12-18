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
struct TYPE_2__ {int sd_lolimit; int sd_hilimit; int sd_lobase; int sd_hibase; int sd_type; int sd_dpl; int sd_p; int /*<<< orphan*/  sd_gran; int /*<<< orphan*/  sd_def32; int /*<<< orphan*/  sd_xx; } ;
union descriptor {TYPE_1__ sd; } ;
struct thread {int* td_retval; } ;
struct linux_modify_ldt_args {int func; int bytecount; union descriptor* ptr; } ;
struct l_descriptor {int limit; int base_addr; int read_exec_only; int contents; int seg_not_present; int /*<<< orphan*/  limit_in_pages; int /*<<< orphan*/  seg_32bit; int /*<<< orphan*/  entry_number; } ;
struct l_desc_struct {int dummy; } ;
struct i386_ldt_args {int num; union descriptor* descs; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  ld ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int SDT_MEMRO ; 
 int copyin (union descriptor*,struct l_descriptor*,int) ; 
 int i386_get_ldt (struct thread*,struct i386_ldt_args*) ; 
 int i386_set_ldt (struct thread*,struct i386_ldt_args*,union descriptor*) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*) ; 
 int subyte (char*,int /*<<< orphan*/ ) ; 

int
linux_modify_ldt(struct thread *td, struct linux_modify_ldt_args *uap)
{
	int error;
	struct i386_ldt_args ldt;
	struct l_descriptor ld;
	union descriptor desc;
	int size, written;

	switch (uap->func) {
	case 0x00: /* read_ldt */
		ldt.start = 0;
		ldt.descs = uap->ptr;
		ldt.num = uap->bytecount / sizeof(union descriptor);
		error = i386_get_ldt(td, &ldt);
		td->td_retval[0] *= sizeof(union descriptor);
		break;
	case 0x02: /* read_default_ldt = 0 */
		size = 5*sizeof(struct l_desc_struct);
		if (size > uap->bytecount)
			size = uap->bytecount;
		for (written = error = 0; written < size && error == 0; written++)
			error = subyte((char *)uap->ptr + written, 0);
		td->td_retval[0] = written;
		break;
	case 0x01: /* write_ldt */
	case 0x11: /* write_ldt */
		if (uap->bytecount != sizeof(ld))
			return (EINVAL);

		error = copyin(uap->ptr, &ld, sizeof(ld));
		if (error)
			return (error);

		ldt.start = ld.entry_number;
		ldt.descs = &desc;
		ldt.num = 1;
		desc.sd.sd_lolimit = (ld.limit & 0x0000ffff);
		desc.sd.sd_hilimit = (ld.limit & 0x000f0000) >> 16;
		desc.sd.sd_lobase = (ld.base_addr & 0x00ffffff);
		desc.sd.sd_hibase = (ld.base_addr & 0xff000000) >> 24;
		desc.sd.sd_type = SDT_MEMRO | ((ld.read_exec_only ^ 1) << 1) |
			(ld.contents << 2);
		desc.sd.sd_dpl = 3;
		desc.sd.sd_p = (ld.seg_not_present ^ 1);
		desc.sd.sd_xx = 0;
		desc.sd.sd_def32 = ld.seg_32bit;
		desc.sd.sd_gran = ld.limit_in_pages;
		error = i386_set_ldt(td, &ldt, &desc);
		break;
	default:
		error = ENOSYS;
		break;
	}

	if (error == EOPNOTSUPP) {
		linux_msg(td, "modify_ldt needs kernel option USER_LDT");
		error = ENOSYS;
	}

	return (error);
}