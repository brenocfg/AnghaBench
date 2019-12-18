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
struct TYPE_2__ {int /*<<< orphan*/  sgl; } ;
struct ib_umem {size_t length; int /*<<< orphan*/  nmap; TYPE_1__ sg_head; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ib_umem_offset (struct ib_umem*) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,size_t,size_t) ; 
 int sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,scalar_t__) ; 

int ib_umem_copy_from(void *dst, struct ib_umem *umem, size_t offset,
		      size_t length)
{
	size_t end = offset + length;
	int ret;

	if (offset > umem->length || length > umem->length - offset) {
		pr_err("ib_umem_copy_from not in range. offset: %zd umem length: %zd end: %zd\n",
		       offset, umem->length, end);
		return -EINVAL;
	}

#ifdef __linux__
	ret = sg_pcopy_to_buffer(umem->sg_head.sgl, umem->nmap, dst, length,
				 offset + ib_umem_offset(umem));
#else
	ret = 0;
#endif
	if (ret < 0)
		return ret;
	else if (ret != length)
		return -EINVAL;
	else
		return 0;
}