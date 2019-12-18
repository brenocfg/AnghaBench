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
struct fw_info {int /*<<< orphan*/  fw_mod_name; int /*<<< orphan*/  kld_name; } ;
struct firmware {int dummy; } ;
struct adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  chip_id (struct adapter*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct fw_info* find_fw_info (int /*<<< orphan*/ ) ; 
 struct firmware* firmware_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
load_fw_module(struct adapter *sc, const struct firmware **dcfg,
    const struct firmware **fw)
{
	struct fw_info *fw_info;

	*dcfg = NULL;
	if (fw != NULL)
		*fw = NULL;

	fw_info = find_fw_info(chip_id(sc));
	if (fw_info == NULL) {
		device_printf(sc->dev,
		    "unable to look up firmware information for chip %d.\n",
		    chip_id(sc));
		return (EINVAL);
	}

	*dcfg = firmware_get(fw_info->kld_name);
	if (*dcfg != NULL) {
		if (fw != NULL)
			*fw = firmware_get(fw_info->fw_mod_name);
		return (0);
	}

	return (ENOENT);
}