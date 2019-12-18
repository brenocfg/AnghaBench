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
typedef  int /*<<< orphan*/  u32 ;
struct notifier_block {int dummy; } ;
struct mce {int bank; int extcpu; } ;
struct cper_sec_mem_err {int dummy; } ;
struct acpi_hest_generic_status {scalar_t__ block_status; } ;
struct acpi_hest_generic_data {int validation_bits; char* fru_text; int error_data_length; scalar_t__ error_severity; scalar_t__ section_type; scalar_t__ fru_id; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPER_SEC_PLATFORM_MEM ; 
 int CPER_SEC_VALID_FRU_ID ; 
 int CPER_SEC_VALID_FRU_TEXT ; 
 int /*<<< orphan*/  ELOG_ENTRY_LEN ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ elog_buf ; 
 struct acpi_hest_generic_status* extlog_elog_entry_check (int,int) ; 
 scalar_t__ guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guid_null ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_extlog_rcd (int /*<<< orphan*/ *,struct acpi_hest_generic_status*,int) ; 
 int /*<<< orphan*/  ras_userspace_consumers () ; 
 int /*<<< orphan*/  trace_extlog_mem_event (struct cper_sec_mem_err*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int extlog_print(struct notifier_block *nb, unsigned long val,
			void *data)
{
	struct mce *mce = (struct mce *)data;
	int	bank = mce->bank;
	int	cpu = mce->extcpu;
	struct acpi_hest_generic_status *estatus, *tmp;
	struct acpi_hest_generic_data *gdata;
	const guid_t *fru_id = &guid_null;
	char *fru_text = "";
	guid_t *sec_type;
	static u32 err_seq;

	estatus = extlog_elog_entry_check(cpu, bank);
	if (estatus == NULL)
		return NOTIFY_DONE;

	memcpy(elog_buf, (void *)estatus, ELOG_ENTRY_LEN);
	/* clear record status to enable BIOS to update it again */
	estatus->block_status = 0;

	tmp = (struct acpi_hest_generic_status *)elog_buf;

	if (!ras_userspace_consumers()) {
		print_extlog_rcd(NULL, tmp, cpu);
		goto out;
	}

	/* log event via trace */
	err_seq++;
	gdata = (struct acpi_hest_generic_data *)(tmp + 1);
	if (gdata->validation_bits & CPER_SEC_VALID_FRU_ID)
		fru_id = (guid_t *)gdata->fru_id;
	if (gdata->validation_bits & CPER_SEC_VALID_FRU_TEXT)
		fru_text = gdata->fru_text;
	sec_type = (guid_t *)gdata->section_type;
	if (guid_equal(sec_type, &CPER_SEC_PLATFORM_MEM)) {
		struct cper_sec_mem_err *mem = (void *)(gdata + 1);
		if (gdata->error_data_length >= sizeof(*mem))
			trace_extlog_mem_event(mem, err_seq, fru_id, fru_text,
					       (u8)gdata->error_severity);
	}

out:
	return NOTIFY_STOP;
}