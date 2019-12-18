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
struct ecore_ooo_buffer {int /*<<< orphan*/  rx_buffer_phys_addr; } ;
struct ecore_ll2_info {int /*<<< orphan*/  my_id; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_ooo_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int ecore_ll2_post_rx_buffer (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_ooo_buffer*,int) ; 
 struct ecore_ooo_buffer* ecore_ooo_get_free_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ooo_put_free_buffer (int /*<<< orphan*/ ,struct ecore_ooo_buffer*) ; 

__attribute__((used)) static void
ecore_ooo_submit_rx_buffers(struct ecore_hwfn *p_hwfn,
			    struct ecore_ll2_info *p_ll2_conn)
{
	struct ecore_ooo_buffer *p_buffer;
	enum _ecore_status_t rc;

	while ((p_buffer = ecore_ooo_get_free_buffer(p_hwfn->p_ooo_info))) {
		rc = ecore_ll2_post_rx_buffer(p_hwfn,
					    p_ll2_conn->my_id,
					    p_buffer->rx_buffer_phys_addr,
					    0, p_buffer, true);
		if (rc != ECORE_SUCCESS) {
			ecore_ooo_put_free_buffer(p_hwfn->p_ooo_info, p_buffer);
			break;
		}
	}
}