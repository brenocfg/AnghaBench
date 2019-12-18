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
struct ecore_ooo_buffer {int /*<<< orphan*/  rx_buffer_size; int /*<<< orphan*/  rx_buffer_phys_addr; int /*<<< orphan*/  rx_buffer_virt_addr; } ;
struct TYPE_2__ {scalar_t__ conn_type; } ;
struct ecore_ll2_info {TYPE_1__ input; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; int /*<<< orphan*/  p_ooo_info; } ;

/* Variables and functions */
 scalar_t__ ECORE_LL2_TYPE_OOO ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_ooo_buffer*) ; 
 struct ecore_ooo_buffer* ecore_ooo_get_free_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ooo_release_all_isles (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ll2_release_connection_ooo(struct ecore_hwfn *p_hwfn,
					     struct ecore_ll2_info *p_ll2_conn)
{
	struct ecore_ooo_buffer *p_buffer;

	if (p_ll2_conn->input.conn_type != ECORE_LL2_TYPE_OOO)
		return;

	ecore_ooo_release_all_isles(p_hwfn->p_ooo_info);
	while ((p_buffer = ecore_ooo_get_free_buffer(p_hwfn->p_ooo_info))) {
		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       p_buffer->rx_buffer_virt_addr,
				       p_buffer->rx_buffer_phys_addr,
				       p_buffer->rx_buffer_size);
		OSAL_FREE(p_hwfn->p_dev, p_buffer);
	}
}