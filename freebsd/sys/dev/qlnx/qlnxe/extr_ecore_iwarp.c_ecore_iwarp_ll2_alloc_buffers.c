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
struct ecore_iwarp_ll2_buff {int buff_size; int /*<<< orphan*/  data; int /*<<< orphan*/  data_phys_addr; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int ECORE_NOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_iwarp_ll2_buff*) ; 
 struct ecore_iwarp_ll2_buff* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ecore_iwarp_ll2_post_rx (struct ecore_hwfn*,struct ecore_iwarp_ll2_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ecore_iwarp_ll2_alloc_buffers(struct ecore_hwfn *p_hwfn,
			      int num_rx_bufs,
			      int buff_size,
			      u8 ll2_handle)
{
	struct ecore_iwarp_ll2_buff *buffer;
	int rc = 0;
	int i;

	for (i = 0; i < num_rx_bufs; i++) {
		buffer = OSAL_ZALLOC(p_hwfn->p_dev,
				     GFP_KERNEL, sizeof(*buffer));
		if (!buffer) {
			DP_INFO(p_hwfn, "Failed to allocate LL2 buffer desc\n");
			break;
		}

		buffer->data =
			OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev,
						&buffer->data_phys_addr,
						buff_size);

		if (!buffer->data) {
			DP_INFO(p_hwfn, "Failed to allocate LL2 buffers\n");
			OSAL_FREE(p_hwfn->p_dev, buffer);
			rc = ECORE_NOMEM;
			break;
		}

		buffer->buff_size = buff_size;
		rc = ecore_iwarp_ll2_post_rx(p_hwfn, buffer, ll2_handle);

		if (rc)
			break; /* buffers will be deallocated by ecore_ll2 */
	}
	return rc;
}