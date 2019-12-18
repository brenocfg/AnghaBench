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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct wpabuf {int dummy; } ;
struct p2p_noa_desc {int count_type; void* interval; void* duration; } ;
typedef  int /*<<< orphan*/  desc2 ;
typedef  int /*<<< orphan*/  desc1 ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_PRESENCE_REQ ; 
 int /*<<< orphan*/  os_memset (struct p2p_noa_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_buf_add_action_hdr (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 int /*<<< orphan*/  p2p_buf_add_noa (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct p2p_noa_desc*,struct p2p_noa_desc*) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc (int) ; 

__attribute__((used)) static struct wpabuf * p2p_build_presence_req(u32 duration1, u32 interval1,
					      u32 duration2, u32 interval2)
{
	struct wpabuf *req;
	struct p2p_noa_desc desc1, desc2, *ptr1 = NULL, *ptr2 = NULL;
	u8 *len;

	req = wpabuf_alloc(100);
	if (req == NULL)
		return NULL;

	if (duration1 || interval1) {
		os_memset(&desc1, 0, sizeof(desc1));
		desc1.count_type = 1;
		desc1.duration = duration1;
		desc1.interval = interval1;
		ptr1 = &desc1;

		if (duration2 || interval2) {
			os_memset(&desc2, 0, sizeof(desc2));
			desc2.count_type = 2;
			desc2.duration = duration2;
			desc2.interval = interval2;
			ptr2 = &desc2;
		}
	}

	p2p_buf_add_action_hdr(req, P2P_PRESENCE_REQ, 1);
	len = p2p_buf_add_ie_hdr(req);
	p2p_buf_add_noa(req, 0, 0, 0, ptr1, ptr2);
	p2p_buf_update_ie_hdr(req, len);

	return req;
}