#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s390_load_data {int /*<<< orphan*/  report; int /*<<< orphan*/  memsz; TYPE_1__* parm; } ;
struct kimage {scalar_t__ type; scalar_t__ initrd_buf_len; int /*<<< orphan*/  initrd_buf; } ;
struct kexec_buf {scalar_t__ memsz; int /*<<< orphan*/  mem; scalar_t__ bufsz; int /*<<< orphan*/  buffer; struct kimage* image; } ;
struct TYPE_4__ {scalar_t__ start; } ;
struct TYPE_3__ {scalar_t__ initrd_size; int /*<<< orphan*/  initrd_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_2__ crashk_res ; 
 int ipl_report_add_component (int /*<<< orphan*/ ,struct kexec_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

__attribute__((used)) static int kexec_file_add_initrd(struct kimage *image,
				 struct s390_load_data *data)
{
	struct kexec_buf buf;
	int ret;

	buf.image = image;

	buf.buffer = image->initrd_buf;
	buf.bufsz = image->initrd_buf_len;

	data->memsz = ALIGN(data->memsz, PAGE_SIZE);
	buf.mem = data->memsz;
	if (image->type == KEXEC_TYPE_CRASH)
		buf.mem += crashk_res.start;
	buf.memsz = buf.bufsz;

	data->parm->initrd_start = buf.mem;
	data->parm->initrd_size = buf.memsz;
	data->memsz += buf.memsz;

	ret = kexec_add_buffer(&buf);
	if (ret)
		return ret;

	return ipl_report_add_component(data->report, &buf, 0, 0);
}