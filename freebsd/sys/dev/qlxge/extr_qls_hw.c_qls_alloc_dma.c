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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 scalar_t__ qls_alloc_mpi_dma (int /*<<< orphan*/ *) ; 
 scalar_t__ qls_alloc_rss_dma (int /*<<< orphan*/ *) ; 
 scalar_t__ qls_alloc_rx_dma (int /*<<< orphan*/ *) ; 
 scalar_t__ qls_alloc_tx_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qls_free_mpi_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qls_free_rx_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qls_free_tx_dma (int /*<<< orphan*/ *) ; 

int
qls_alloc_dma(qla_host_t *ha)
{
	if (qls_alloc_rx_dma(ha))
		return (-1);

	if (qls_alloc_tx_dma(ha)) {
		qls_free_rx_dma(ha);
		return (-1);
	}

	if (qls_alloc_mpi_dma(ha)) {
		qls_free_tx_dma(ha);
		qls_free_rx_dma(ha);
		return (-1);
	}

	if (qls_alloc_rss_dma(ha)) {
		qls_free_mpi_dma(ha);
		qls_free_tx_dma(ha);
		qls_free_rx_dma(ha);
		return (-1);
	}

	return (0);
}