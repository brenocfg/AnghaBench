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
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int ecc_sym_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd64_warn (char*,int) ; 
 int decode_syndrome (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int map_err_sym_to_channel (int,int) ; 
 int /*<<< orphan*/  x4_vectors ; 
 int /*<<< orphan*/  x8_vectors ; 

__attribute__((used)) static int get_channel_from_ecc_syndrome(struct mem_ctl_info *mci, u16 syndrome)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	int err_sym = -1;

	if (pvt->ecc_sym_sz == 8)
		err_sym = decode_syndrome(syndrome, x8_vectors,
					  ARRAY_SIZE(x8_vectors),
					  pvt->ecc_sym_sz);
	else if (pvt->ecc_sym_sz == 4)
		err_sym = decode_syndrome(syndrome, x4_vectors,
					  ARRAY_SIZE(x4_vectors),
					  pvt->ecc_sym_sz);
	else {
		amd64_warn("Illegal syndrome type: %u\n", pvt->ecc_sym_sz);
		return err_sym;
	}

	return map_err_sym_to_channel(err_sym, pvt->ecc_sym_sz);
}