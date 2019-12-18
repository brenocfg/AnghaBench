#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s390_load_data {scalar_t__ memsz; int /*<<< orphan*/  report; void* parm; void* kernel_mem; void* kernel_buf; } ;
struct kimage {scalar_t__ type; void* kernel_buf; } ;
struct kexec_buf {scalar_t__ memsz; void* buffer; void* mem; int /*<<< orphan*/  bufsz; struct kimage* image; } ;
struct TYPE_6__ {scalar_t__ start; } ;
struct TYPE_5__ {scalar_t__ e_entry; int e_phoff; int e_phnum; } ;
struct TYPE_4__ {scalar_t__ p_type; int p_offset; scalar_t__ p_paddr; scalar_t__ p_memsz; int /*<<< orphan*/  p_align; int /*<<< orphan*/  p_filesz; } ;
typedef  TYPE_1__ Elf_Phdr ;
typedef  TYPE_2__ Elf_Ehdr ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 void* ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPL_RB_CERT_UNKNOWN ; 
 int IPL_RB_COMPONENT_FLAG_SIGNED ; 
 int IPL_RB_COMPONENT_FLAG_VERIFIED ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int PARMAREA ; 
 scalar_t__ PT_LOAD ; 
 scalar_t__ STARTUP_KDUMP_OFFSET ; 
 TYPE_3__ crashk_res ; 
 int /*<<< orphan*/  ipl_report_add_component (int /*<<< orphan*/ ,struct kexec_buf*,int,int /*<<< orphan*/ ) ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

__attribute__((used)) static int kexec_file_add_kernel_elf(struct kimage *image,
				     struct s390_load_data *data)
{
	struct kexec_buf buf;
	const Elf_Ehdr *ehdr;
	const Elf_Phdr *phdr;
	Elf_Addr entry;
	void *kernel;
	int i, ret;

	kernel = image->kernel_buf;
	ehdr = (Elf_Ehdr *)kernel;
	buf.image = image;
	if (image->type == KEXEC_TYPE_CRASH)
		entry = STARTUP_KDUMP_OFFSET;
	else
		entry = ehdr->e_entry;

	phdr = (void *)ehdr + ehdr->e_phoff;
	for (i = 0; i < ehdr->e_phnum; i++, phdr++) {
		if (phdr->p_type != PT_LOAD)
			continue;

		buf.buffer = kernel + phdr->p_offset;
		buf.bufsz = phdr->p_filesz;

		buf.mem = ALIGN(phdr->p_paddr, phdr->p_align);
		if (image->type == KEXEC_TYPE_CRASH)
			buf.mem += crashk_res.start;
		buf.memsz = phdr->p_memsz;
		data->memsz = ALIGN(data->memsz, phdr->p_align) + buf.memsz;

		if (entry - phdr->p_paddr < phdr->p_memsz) {
			data->kernel_buf = buf.buffer;
			data->kernel_mem = buf.mem;
			data->parm = buf.buffer + PARMAREA;
		}

		ipl_report_add_component(data->report, &buf,
					 IPL_RB_COMPONENT_FLAG_SIGNED |
					 IPL_RB_COMPONENT_FLAG_VERIFIED,
					 IPL_RB_CERT_UNKNOWN);
		ret = kexec_add_buffer(&buf);
		if (ret)
			return ret;
	}

	return data->memsz ? 0 : -EINVAL;
}