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
struct ena_adapter {int /*<<< orphan*/  tx_buf_tag; scalar_t__ max_tx_sgl_size; int /*<<< orphan*/  dma_width; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  ENA_DMA_BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_TSO_MAXSIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ena_setup_tx_dma_tag(struct ena_adapter *adapter)
{
	int ret;

	/* Create DMA tag for Tx buffers */
	ret = bus_dma_tag_create(bus_get_dma_tag(adapter->pdev),
	    1, 0,				  /* alignment, bounds 	     */
	    ENA_DMA_BIT_MASK(adapter->dma_width), /* lowaddr of excl window  */
	    BUS_SPACE_MAXADDR, 			  /* highaddr of excl window */
	    NULL, NULL,				  /* filter, filterarg 	     */
	    ENA_TSO_MAXSIZE,			  /* maxsize 		     */
	    adapter->max_tx_sgl_size - 1,	  /* nsegments 		     */
	    ENA_TSO_MAXSIZE,			  /* maxsegsize 	     */
	    0,					  /* flags 		     */
	    NULL,				  /* lockfunc 		     */
	    NULL,				  /* lockfuncarg 	     */
	    &adapter->tx_buf_tag);

	return (ret);
}