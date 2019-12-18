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
typedef  size_t u8 ;
typedef  size_t u64 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {size_t counter_info_version_in; int /*<<< orphan*/  secondary_index; void* starting_index; void* counter_request; } ;
struct hv_gpci_request_buffer {size_t* bytes; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  HGPCI_REQ_BUFFER_SIZE ; 
 int /*<<< orphan*/  H_GET_PERF_COUNTER_INFO ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (size_t) ; 
 scalar_t__ get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_gpci_reqb ; 
 int /*<<< orphan*/  memset (struct hv_gpci_request_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (struct hv_gpci_request_buffer*) ; 

__attribute__((used)) static unsigned long single_gpci_request(u32 req, u32 starting_index,
		u16 secondary_index, u8 version_in, u32 offset, u8 length,
		u64 *value)
{
	unsigned long ret;
	size_t i;
	u64 count;
	struct hv_gpci_request_buffer *arg;

	arg = (void *)get_cpu_var(hv_gpci_reqb);
	memset(arg, 0, HGPCI_REQ_BUFFER_SIZE);

	arg->params.counter_request = cpu_to_be32(req);
	arg->params.starting_index = cpu_to_be32(starting_index);
	arg->params.secondary_index = cpu_to_be16(secondary_index);
	arg->params.counter_info_version_in = version_in;

	ret = plpar_hcall_norets(H_GET_PERF_COUNTER_INFO,
			virt_to_phys(arg), HGPCI_REQ_BUFFER_SIZE);
	if (ret) {
		pr_devel("hcall failed: 0x%lx\n", ret);
		goto out;
	}

	/*
	 * we verify offset and length are within the zeroed buffer at event
	 * init.
	 */
	count = 0;
	for (i = offset; i < offset + length; i++)
		count |= arg->bytes[i] << (i - offset);

	*value = count;
out:
	put_cpu_var(hv_gpci_reqb);
	return ret;
}