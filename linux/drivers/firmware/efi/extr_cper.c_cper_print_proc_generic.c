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
struct cper_sec_proc_generic {int validation_bits; size_t proc_type; size_t proc_isa; size_t operation; int /*<<< orphan*/  ip; int /*<<< orphan*/  responder_id; int /*<<< orphan*/  requestor_id; int /*<<< orphan*/  target_addr; int /*<<< orphan*/  proc_id; int /*<<< orphan*/  cpu_version; int /*<<< orphan*/  level; int /*<<< orphan*/  flags; int /*<<< orphan*/  proc_error_type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int CPER_PROC_VALID_ERROR_TYPE ; 
 int CPER_PROC_VALID_FLAGS ; 
 int CPER_PROC_VALID_ID ; 
 int CPER_PROC_VALID_IP ; 
 int CPER_PROC_VALID_ISA ; 
 int CPER_PROC_VALID_LEVEL ; 
 int CPER_PROC_VALID_OPERATION ; 
 int CPER_PROC_VALID_REQUESTOR_ID ; 
 int CPER_PROC_VALID_RESPONDER_ID ; 
 int CPER_PROC_VALID_TARGET_ADDRESS ; 
 int CPER_PROC_VALID_TYPE ; 
 int CPER_PROC_VALID_VERSION ; 
 int /*<<< orphan*/  cper_print_bits (char const*,int /*<<< orphan*/ ,char**,size_t) ; 
 char** cper_proc_error_type_strs ; 
 int /*<<< orphan*/  printk (char*,char const*,size_t,...) ; 
 char** proc_flag_strs ; 
 char** proc_isa_strs ; 
 char** proc_op_strs ; 
 char** proc_type_strs ; 

__attribute__((used)) static void cper_print_proc_generic(const char *pfx,
				    const struct cper_sec_proc_generic *proc)
{
	if (proc->validation_bits & CPER_PROC_VALID_TYPE)
		printk("%s""processor_type: %d, %s\n", pfx, proc->proc_type,
		       proc->proc_type < ARRAY_SIZE(proc_type_strs) ?
		       proc_type_strs[proc->proc_type] : "unknown");
	if (proc->validation_bits & CPER_PROC_VALID_ISA)
		printk("%s""processor_isa: %d, %s\n", pfx, proc->proc_isa,
		       proc->proc_isa < ARRAY_SIZE(proc_isa_strs) ?
		       proc_isa_strs[proc->proc_isa] : "unknown");
	if (proc->validation_bits & CPER_PROC_VALID_ERROR_TYPE) {
		printk("%s""error_type: 0x%02x\n", pfx, proc->proc_error_type);
		cper_print_bits(pfx, proc->proc_error_type,
				cper_proc_error_type_strs,
				ARRAY_SIZE(cper_proc_error_type_strs));
	}
	if (proc->validation_bits & CPER_PROC_VALID_OPERATION)
		printk("%s""operation: %d, %s\n", pfx, proc->operation,
		       proc->operation < ARRAY_SIZE(proc_op_strs) ?
		       proc_op_strs[proc->operation] : "unknown");
	if (proc->validation_bits & CPER_PROC_VALID_FLAGS) {
		printk("%s""flags: 0x%02x\n", pfx, proc->flags);
		cper_print_bits(pfx, proc->flags, proc_flag_strs,
				ARRAY_SIZE(proc_flag_strs));
	}
	if (proc->validation_bits & CPER_PROC_VALID_LEVEL)
		printk("%s""level: %d\n", pfx, proc->level);
	if (proc->validation_bits & CPER_PROC_VALID_VERSION)
		printk("%s""version_info: 0x%016llx\n", pfx, proc->cpu_version);
	if (proc->validation_bits & CPER_PROC_VALID_ID)
		printk("%s""processor_id: 0x%016llx\n", pfx, proc->proc_id);
	if (proc->validation_bits & CPER_PROC_VALID_TARGET_ADDRESS)
		printk("%s""target_address: 0x%016llx\n",
		       pfx, proc->target_addr);
	if (proc->validation_bits & CPER_PROC_VALID_REQUESTOR_ID)
		printk("%s""requestor_id: 0x%016llx\n",
		       pfx, proc->requestor_id);
	if (proc->validation_bits & CPER_PROC_VALID_RESPONDER_ID)
		printk("%s""responder_id: 0x%016llx\n",
		       pfx, proc->responder_id);
	if (proc->validation_bits & CPER_PROC_VALID_IP)
		printk("%s""IP: 0x%016llx\n", pfx, proc->ip);
}