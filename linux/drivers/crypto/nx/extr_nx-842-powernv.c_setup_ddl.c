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
struct data_descriptor_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDE_BUFFER_ALIGN ; 
 unsigned int DDE_BUFFER_LAST_MULT ; 
 int DDL_LEN_MAX ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned int LEN_ON_PAGE (unsigned long) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long nx842_get_pa (unsigned char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 unsigned int round_down (unsigned int,unsigned int) ; 
 int setup_direct_dde (struct data_descriptor_entry*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  setup_indirect_dde (struct data_descriptor_entry*,struct data_descriptor_entry*,int,int) ; 

__attribute__((used)) static int setup_ddl(struct data_descriptor_entry *dde,
		     struct data_descriptor_entry *ddl,
		     unsigned char *buf, unsigned int len,
		     bool in)
{
	unsigned long pa = nx842_get_pa(buf);
	int i, ret, total_len = len;

	if (!IS_ALIGNED(pa, DDE_BUFFER_ALIGN)) {
		pr_debug("%s buffer pa 0x%lx not 0x%x-byte aligned\n",
			 in ? "input" : "output", pa, DDE_BUFFER_ALIGN);
		return -EINVAL;
	}

	/* only need to check last mult; since buffer must be
	 * DDE_BUFFER_ALIGN aligned, and that is a multiple of
	 * DDE_BUFFER_SIZE_MULT, and pre-last page DDE buffers
	 * are guaranteed a multiple of DDE_BUFFER_SIZE_MULT.
	 */
	if (len % DDE_BUFFER_LAST_MULT) {
		pr_debug("%s buffer len 0x%x not a multiple of 0x%x\n",
			 in ? "input" : "output", len, DDE_BUFFER_LAST_MULT);
		if (in)
			return -EINVAL;
		len = round_down(len, DDE_BUFFER_LAST_MULT);
	}

	/* use a single direct DDE */
	if (len <= LEN_ON_PAGE(pa)) {
		ret = setup_direct_dde(dde, pa, len);
		WARN_ON(ret < len);
		return 0;
	}

	/* use the DDL */
	for (i = 0; i < DDL_LEN_MAX && len > 0; i++) {
		ret = setup_direct_dde(&ddl[i], pa, len);
		buf += ret;
		len -= ret;
		pa = nx842_get_pa(buf);
	}

	if (len > 0) {
		pr_debug("0x%x total %s bytes 0x%x too many for DDL.\n",
			 total_len, in ? "input" : "output", len);
		if (in)
			return -EMSGSIZE;
		total_len -= len;
	}
	setup_indirect_dde(dde, ddl, i, total_len);

	return 0;
}