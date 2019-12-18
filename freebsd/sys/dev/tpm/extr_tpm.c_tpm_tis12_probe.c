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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_ACCESS ; 
 int TPM_ACCESS_ACTIVE_LOCALITY ; 
 int TPM_ACCESS_REQUEST_USE ; 
 int TPM_ACCESS_VALID ; 
 int /*<<< orphan*/  TPM_CAPBITS ; 
 int TPM_CAPSREQ ; 
 int /*<<< orphan*/  TPM_ID ; 
 int /*<<< orphan*/  TPM_INTF_CAPABILITIES ; 
 int TPM_INTF_INT_EDGE_RISING ; 
 int TPM_INTF_INT_LEVEL_LOW ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ) ; 

int
tpm_tis12_probe(bus_space_tag_t bt, bus_space_handle_t bh)
{
	u_int32_t r;
	u_int8_t save, reg;

	r = bus_space_read_4(bt, bh, TPM_INTF_CAPABILITIES);
	if (r == 0xffffffff)
		return 0;

#ifdef TPM_DEBUG
	printf("tpm: caps=%b\n", r, TPM_CAPBITS);
#endif
	if ((r & TPM_CAPSREQ) != TPM_CAPSREQ ||
	    !(r & (TPM_INTF_INT_EDGE_RISING | TPM_INTF_INT_LEVEL_LOW))) {
#ifdef TPM_DEBUG
		printf("tpm: caps too low (caps=%b)\n", r, TPM_CAPBITS);
#endif
		return 0;
	}

	save = bus_space_read_1(bt, bh, TPM_ACCESS);
	bus_space_write_1(bt, bh, TPM_ACCESS, TPM_ACCESS_REQUEST_USE);
	reg = bus_space_read_1(bt, bh, TPM_ACCESS);
	if ((reg & TPM_ACCESS_VALID) && (reg & TPM_ACCESS_ACTIVE_LOCALITY) &&
	    bus_space_read_4(bt, bh, TPM_ID) != 0xffffffff)
		return 1;

	bus_space_write_1(bt, bh, TPM_ACCESS, save);
	return 0;
}