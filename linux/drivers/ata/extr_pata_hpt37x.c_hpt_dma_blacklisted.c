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
struct ata_device {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  model_num ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_ID_PROD_LEN ; 
 int /*<<< orphan*/  ata_id_c_string (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int match_string (char const* const*,int,unsigned char*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,char const* const) ; 

__attribute__((used)) static int hpt_dma_blacklisted(const struct ata_device *dev, char *modestr,
			       const char * const list[])
{
	unsigned char model_num[ATA_ID_PROD_LEN + 1];
	int i;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, sizeof(model_num));

	i = match_string(list, -1, model_num);
	if (i >= 0) {
		pr_warn("%s is not supported for %s\n", modestr, list[i]);
		return 1;
	}
	return 0;
}