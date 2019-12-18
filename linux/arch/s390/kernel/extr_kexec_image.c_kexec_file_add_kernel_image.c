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
struct s390_load_data {int /*<<< orphan*/  report; int /*<<< orphan*/  memsz; scalar_t__ parm; scalar_t__ kernel_mem; scalar_t__ kernel_buf; } ;
struct kimage {scalar_t__ type; scalar_t__ kernel_buf; scalar_t__ kernel_buf_len; } ;
struct kexec_buf {scalar_t__ memsz; scalar_t__ mem; scalar_t__ bufsz; scalar_t__ buffer; struct kimage* image; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPL_RB_CERT_UNKNOWN ; 
 int IPL_RB_COMPONENT_FLAG_SIGNED ; 
 int IPL_RB_COMPONENT_FLAG_VERIFIED ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 scalar_t__ PARMAREA ; 
 TYPE_1__ crashk_res ; 
 int /*<<< orphan*/  ipl_report_add_component (int /*<<< orphan*/ ,struct kexec_buf*,int,int /*<<< orphan*/ ) ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

__attribute__((used)) static int kexec_file_add_kernel_image(struct kimage *image,
				       struct s390_load_data *data)
{
	struct kexec_buf buf;

	buf.image = image;

	buf.buffer = image->kernel_buf;
	buf.bufsz = image->kernel_buf_len;

	buf.mem = 0;
	if (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;
	buf.memsz = buf.bufsz;

	data->kernel_buf = image->kernel_buf;
	data->kernel_mem = buf.mem;
	data->parm = image->kernel_buf + PARMAREA;
	data->memsz += buf.memsz;

	ipl_report_add_component(data->report, &buf,
				 IPL_RB_COMPONENT_FLAG_SIGNED |
				 IPL_RB_COMPONENT_FLAG_VERIFIED,
				 IPL_RB_CERT_UNKNOWN);
	return kexec_add_buffer(&buf);
}