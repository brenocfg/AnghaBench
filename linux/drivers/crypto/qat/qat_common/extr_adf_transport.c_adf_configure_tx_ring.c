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
typedef  int /*<<< orphan*/  uint32_t ;
struct adf_etr_ring_data {int /*<<< orphan*/  ring_number; TYPE_1__* bank; int /*<<< orphan*/  ring_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_RING_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CSR_RING_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adf_configure_tx_ring(struct adf_etr_ring_data *ring)
{
	uint32_t ring_config = BUILD_RING_CONFIG(ring->ring_size);

	WRITE_CSR_RING_CONFIG(ring->bank->csr_addr, ring->bank->bank_number,
			      ring->ring_number, ring_config);
}