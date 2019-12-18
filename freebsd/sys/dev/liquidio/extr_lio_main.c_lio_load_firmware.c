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
struct octeon_device {int dummy; } ;
struct firmware {int /*<<< orphan*/  datasize; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {char* card_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 char* LIO_FW_BASE_NAME ; 
 int /*<<< orphan*/  LIO_FW_NAME_SUFFIX ; 
 char* LIO_FW_NAME_TYPE_NIC ; 
 int LIO_MAX_FW_FILENAME_LEN ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 char* fw_type ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,char*) ; 
 int lio_download_firmware (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lio_get_conf (struct octeon_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_load_firmware(struct octeon_device *oct)
{
	const struct firmware	*fw;
	char	*tmp_fw_type = NULL;
	int	ret = 0;
	char	fw_name[LIO_MAX_FW_FILENAME_LEN];

	if (fw_type[0] == '\0')
		tmp_fw_type = LIO_FW_NAME_TYPE_NIC;
	else
		tmp_fw_type = fw_type;

	sprintf(fw_name, "%s%s_%s%s", LIO_FW_BASE_NAME,
		lio_get_conf(oct)->card_name, tmp_fw_type, LIO_FW_NAME_SUFFIX);

	fw = firmware_get(fw_name);
	if (fw == NULL) {
		lio_dev_err(oct, "Request firmware failed. Could not find file %s.\n",
			    fw_name);
		return (EINVAL);
	}

	ret = lio_download_firmware(oct, fw->data, fw->datasize);

	firmware_put(fw, FIRMWARE_UNLOAD);

	return (ret);
}