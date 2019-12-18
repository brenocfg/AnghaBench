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
struct hv_24x7_request_buffer {int /*<<< orphan*/  failing_request_ix; int /*<<< orphan*/  detailed_rc; struct hv_24x7_request* requests; } ;
struct hv_24x7_request {int /*<<< orphan*/  starting_lpar_ix; int /*<<< orphan*/  starting_ix; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  performance_domain; } ;
struct hv_24x7_data_result_buffer {int /*<<< orphan*/  failing_request_ix; int /*<<< orphan*/  detailed_rc; struct hv_24x7_request* requests; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  H24x7_DATA_BUFFER_SIZE ; 
 int /*<<< orphan*/  H_GET_24X7_DATA ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (struct hv_24x7_request_buffer*) ; 

__attribute__((used)) static int make_24x7_request(struct hv_24x7_request_buffer *request_buffer,
			     struct hv_24x7_data_result_buffer *result_buffer)
{
	long ret;

	/*
	 * NOTE: Due to variable number of array elements in request and
	 *	 result buffer(s), sizeof() is not reliable. Use the actual
	 *	 allocated buffer size, H24x7_DATA_BUFFER_SIZE.
	 */
	ret = plpar_hcall_norets(H_GET_24X7_DATA,
			virt_to_phys(request_buffer), H24x7_DATA_BUFFER_SIZE,
			virt_to_phys(result_buffer),  H24x7_DATA_BUFFER_SIZE);

	if (ret) {
		struct hv_24x7_request *req;

		req = request_buffer->requests;
		pr_notice_ratelimited("hcall failed: [%d %#x %#x %d] => ret 0x%lx (%ld) detail=0x%x failing ix=%x\n",
				      req->performance_domain, req->data_offset,
				      req->starting_ix, req->starting_lpar_ix,
				      ret, ret, result_buffer->detailed_rc,
				      result_buffer->failing_request_ix);
		return -EIO;
	}

	return 0;
}