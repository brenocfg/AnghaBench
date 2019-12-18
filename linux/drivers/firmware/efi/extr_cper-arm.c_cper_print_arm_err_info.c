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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  CPER_ARM_BUS_ERROR 130 
#define  CPER_ARM_CACHE_ERROR 129 
 int CPER_ARM_ERR_ACCESS_MODE_MASK ; 
 int CPER_ARM_ERR_ACCESS_MODE_SHIFT ; 
 int CPER_ARM_ERR_ADDRESS_SPACE_MASK ; 
 int CPER_ARM_ERR_ADDRESS_SPACE_SHIFT ; 
 int CPER_ARM_ERR_CORRECTED_MASK ; 
 int CPER_ARM_ERR_CORRECTED_SHIFT ; 
 int CPER_ARM_ERR_LEVEL_MASK ; 
 int CPER_ARM_ERR_LEVEL_SHIFT ; 
 int CPER_ARM_ERR_MEM_ATTRIBUTES_MASK ; 
 int CPER_ARM_ERR_MEM_ATTRIBUTES_SHIFT ; 
 int CPER_ARM_ERR_OPERATION_MASK ; 
 int CPER_ARM_ERR_OPERATION_SHIFT ; 
 int CPER_ARM_ERR_PARTICIPATION_TYPE_MASK ; 
 int CPER_ARM_ERR_PARTICIPATION_TYPE_SHIFT ; 
 int CPER_ARM_ERR_PC_CORRUPT_MASK ; 
 int CPER_ARM_ERR_PC_CORRUPT_SHIFT ; 
 int CPER_ARM_ERR_PRECISE_PC_MASK ; 
 int CPER_ARM_ERR_PRECISE_PC_SHIFT ; 
 int CPER_ARM_ERR_RESTARTABLE_PC_MASK ; 
 int CPER_ARM_ERR_RESTARTABLE_PC_SHIFT ; 
 int CPER_ARM_ERR_TIME_OUT_MASK ; 
 int CPER_ARM_ERR_TIME_OUT_SHIFT ; 
 int CPER_ARM_ERR_TRANSACTION_MASK ; 
 int CPER_ARM_ERR_TRANSACTION_SHIFT ; 
 int CPER_ARM_ERR_VALID_ACCESS_MODE ; 
 int CPER_ARM_ERR_VALID_ADDRESS_SPACE ; 
 int CPER_ARM_ERR_VALID_CORRECTED ; 
 int CPER_ARM_ERR_VALID_LEVEL ; 
 int CPER_ARM_ERR_VALID_MEM_ATTRIBUTES ; 
 int CPER_ARM_ERR_VALID_OPERATION_TYPE ; 
 int CPER_ARM_ERR_VALID_PARTICIPATION_TYPE ; 
 int CPER_ARM_ERR_VALID_PRECISE_PC ; 
 int CPER_ARM_ERR_VALID_PROC_CONTEXT_CORRUPT ; 
 int CPER_ARM_ERR_VALID_RESTARTABLE_PC ; 
 int CPER_ARM_ERR_VALID_TIME_OUT ; 
 int CPER_ARM_ERR_VALID_TRANSACTION_TYPE ; 
 int CPER_ARM_MAX_TYPE ; 
#define  CPER_ARM_TLB_ERROR 128 
 int CPER_ARM_VENDOR_ERROR ; 
 int /*<<< orphan*/ * arm_bus_err_addr_space_strs ; 
 int /*<<< orphan*/ * arm_bus_err_op_strs ; 
 int /*<<< orphan*/ * arm_bus_err_part_type_strs ; 
 int /*<<< orphan*/ * arm_cache_err_op_strs ; 
 int /*<<< orphan*/ * arm_err_trans_type_strs ; 
 int /*<<< orphan*/ * arm_tlb_err_op_strs ; 
 int /*<<< orphan*/  printk (char*,char const*,...) ; 

__attribute__((used)) static void cper_print_arm_err_info(const char *pfx, u32 type,
				    u64 error_info)
{
	u8 trans_type, op_type, level, participation_type, address_space;
	u16 mem_attributes;
	bool proc_context_corrupt, corrected, precise_pc, restartable_pc;
	bool time_out, access_mode;

	/* If the type is unknown, bail. */
	if (type > CPER_ARM_MAX_TYPE)
		return;

	/*
	 * Vendor type errors have error information values that are vendor
	 * specific.
	 */
	if (type == CPER_ARM_VENDOR_ERROR)
		return;

	if (error_info & CPER_ARM_ERR_VALID_TRANSACTION_TYPE) {
		trans_type = ((error_info >> CPER_ARM_ERR_TRANSACTION_SHIFT)
			      & CPER_ARM_ERR_TRANSACTION_MASK);
		if (trans_type < ARRAY_SIZE(arm_err_trans_type_strs)) {
			printk("%stransaction type: %s\n", pfx,
			       arm_err_trans_type_strs[trans_type]);
		}
	}

	if (error_info & CPER_ARM_ERR_VALID_OPERATION_TYPE) {
		op_type = ((error_info >> CPER_ARM_ERR_OPERATION_SHIFT)
			   & CPER_ARM_ERR_OPERATION_MASK);
		switch (type) {
		case CPER_ARM_CACHE_ERROR:
			if (op_type < ARRAY_SIZE(arm_cache_err_op_strs)) {
				printk("%soperation type: %s\n", pfx,
				       arm_cache_err_op_strs[op_type]);
			}
			break;
		case CPER_ARM_TLB_ERROR:
			if (op_type < ARRAY_SIZE(arm_tlb_err_op_strs)) {
				printk("%soperation type: %s\n", pfx,
				       arm_tlb_err_op_strs[op_type]);
			}
			break;
		case CPER_ARM_BUS_ERROR:
			if (op_type < ARRAY_SIZE(arm_bus_err_op_strs)) {
				printk("%soperation type: %s\n", pfx,
				       arm_bus_err_op_strs[op_type]);
			}
			break;
		}
	}

	if (error_info & CPER_ARM_ERR_VALID_LEVEL) {
		level = ((error_info >> CPER_ARM_ERR_LEVEL_SHIFT)
			 & CPER_ARM_ERR_LEVEL_MASK);
		switch (type) {
		case CPER_ARM_CACHE_ERROR:
			printk("%scache level: %d\n", pfx, level);
			break;
		case CPER_ARM_TLB_ERROR:
			printk("%sTLB level: %d\n", pfx, level);
			break;
		case CPER_ARM_BUS_ERROR:
			printk("%saffinity level at which the bus error occurred: %d\n",
			       pfx, level);
			break;
		}
	}

	if (error_info & CPER_ARM_ERR_VALID_PROC_CONTEXT_CORRUPT) {
		proc_context_corrupt = ((error_info >> CPER_ARM_ERR_PC_CORRUPT_SHIFT)
					& CPER_ARM_ERR_PC_CORRUPT_MASK);
		if (proc_context_corrupt)
			printk("%sprocessor context corrupted\n", pfx);
		else
			printk("%sprocessor context not corrupted\n", pfx);
	}

	if (error_info & CPER_ARM_ERR_VALID_CORRECTED) {
		corrected = ((error_info >> CPER_ARM_ERR_CORRECTED_SHIFT)
			     & CPER_ARM_ERR_CORRECTED_MASK);
		if (corrected)
			printk("%sthe error has been corrected\n", pfx);
		else
			printk("%sthe error has not been corrected\n", pfx);
	}

	if (error_info & CPER_ARM_ERR_VALID_PRECISE_PC) {
		precise_pc = ((error_info >> CPER_ARM_ERR_PRECISE_PC_SHIFT)
			      & CPER_ARM_ERR_PRECISE_PC_MASK);
		if (precise_pc)
			printk("%sPC is precise\n", pfx);
		else
			printk("%sPC is imprecise\n", pfx);
	}

	if (error_info & CPER_ARM_ERR_VALID_RESTARTABLE_PC) {
		restartable_pc = ((error_info >> CPER_ARM_ERR_RESTARTABLE_PC_SHIFT)
				  & CPER_ARM_ERR_RESTARTABLE_PC_MASK);
		if (restartable_pc)
			printk("%sProgram execution can be restarted reliably at the PC associated with the error.\n", pfx);
	}

	/* The rest of the fields are specific to bus errors */
	if (type != CPER_ARM_BUS_ERROR)
		return;

	if (error_info & CPER_ARM_ERR_VALID_PARTICIPATION_TYPE) {
		participation_type = ((error_info >> CPER_ARM_ERR_PARTICIPATION_TYPE_SHIFT)
				      & CPER_ARM_ERR_PARTICIPATION_TYPE_MASK);
		if (participation_type < ARRAY_SIZE(arm_bus_err_part_type_strs)) {
			printk("%sparticipation type: %s\n", pfx,
			       arm_bus_err_part_type_strs[participation_type]);
		}
	}

	if (error_info & CPER_ARM_ERR_VALID_TIME_OUT) {
		time_out = ((error_info >> CPER_ARM_ERR_TIME_OUT_SHIFT)
			    & CPER_ARM_ERR_TIME_OUT_MASK);
		if (time_out)
			printk("%srequest timed out\n", pfx);
	}

	if (error_info & CPER_ARM_ERR_VALID_ADDRESS_SPACE) {
		address_space = ((error_info >> CPER_ARM_ERR_ADDRESS_SPACE_SHIFT)
				 & CPER_ARM_ERR_ADDRESS_SPACE_MASK);
		if (address_space < ARRAY_SIZE(arm_bus_err_addr_space_strs)) {
			printk("%saddress space: %s\n", pfx,
			       arm_bus_err_addr_space_strs[address_space]);
		}
	}

	if (error_info & CPER_ARM_ERR_VALID_MEM_ATTRIBUTES) {
		mem_attributes = ((error_info >> CPER_ARM_ERR_MEM_ATTRIBUTES_SHIFT)
				  & CPER_ARM_ERR_MEM_ATTRIBUTES_MASK);
		printk("%smemory access attributes:0x%x\n", pfx, mem_attributes);
	}

	if (error_info & CPER_ARM_ERR_VALID_ACCESS_MODE) {
		access_mode = ((error_info >> CPER_ARM_ERR_ACCESS_MODE_SHIFT)
			       & CPER_ARM_ERR_ACCESS_MODE_MASK);
		if (access_mode)
			printk("%saccess mode: normal\n", pfx);
		else
			printk("%saccess mode: secure\n", pfx);
	}
}