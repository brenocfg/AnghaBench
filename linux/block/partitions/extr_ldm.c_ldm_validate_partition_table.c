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
struct partition {int dummy; } ;
struct parsed_partitions {int dummy; } ;
typedef  scalar_t__ __le16 ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ LDM_PARTITION ; 
 int /*<<< orphan*/  MSDOS_LABEL_MAGIC ; 
 scalar_t__ SYS_IND (struct partition*) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldm_debug (char*) ; 
 int /*<<< orphan*/  ldm_info (char*) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_part_sector (struct parsed_partitions*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ldm_validate_partition_table(struct parsed_partitions *state)
{
	Sector sect;
	u8 *data;
	struct partition *p;
	int i;
	bool result = false;

	BUG_ON(!state);

	data = read_part_sector(state, 0, &sect);
	if (!data) {
		ldm_info ("Disk read failed.");
		return false;
	}

	if (*(__le16*) (data + 0x01FE) != cpu_to_le16 (MSDOS_LABEL_MAGIC))
		goto out;

	p = (struct partition*)(data + 0x01BE);
	for (i = 0; i < 4; i++, p++)
		if (SYS_IND (p) == LDM_PARTITION) {
			result = true;
			break;
		}

	if (result)
		ldm_debug ("Found W2K dynamic disk partition type.");

out:
	put_dev_sector (sect);
	return result;
}