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
typedef  scalar_t__ u32 ;
struct equiv_cpu_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONTAINER_HDR_SZ ; 
 scalar_t__ UCODE_EQUIV_CPU_TABLE_TYPE ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  verify_container (int /*<<< orphan*/  const*,size_t,int) ; 

__attribute__((used)) static bool verify_equivalence_table(const u8 *buf, size_t buf_size, bool early)
{
	const u32 *hdr = (const u32 *)buf;
	u32 cont_type, equiv_tbl_len;

	if (!verify_container(buf, buf_size, early))
		return false;

	cont_type = hdr[1];
	if (cont_type != UCODE_EQUIV_CPU_TABLE_TYPE) {
		if (!early)
			pr_debug("Wrong microcode container equivalence table type: %u.\n",
			       cont_type);

		return false;
	}

	buf_size -= CONTAINER_HDR_SZ;

	equiv_tbl_len = hdr[2];
	if (equiv_tbl_len < sizeof(struct equiv_cpu_entry) ||
	    buf_size < equiv_tbl_len) {
		if (!early)
			pr_debug("Truncated equivalence table.\n");

		return false;
	}

	return true;
}