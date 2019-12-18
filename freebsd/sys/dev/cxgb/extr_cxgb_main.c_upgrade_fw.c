#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct firmware {int /*<<< orphan*/  datasize; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fw_version; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int FW_FNAME ; 
 int G_FW_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int G_FW_VERSION_MICRO (int /*<<< orphan*/ ) ; 
 int G_FW_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct firmware* firmware_get (int) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int,int,int) ; 
 int /*<<< orphan*/  t3_get_fw_version (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int t3_load_fw (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upgrade_fw(adapter_t *sc)
{
	const struct firmware *fw;
	int status;
	u32 vers;
	
	if ((fw = firmware_get(FW_FNAME)) == NULL)  {
		device_printf(sc->dev, "Could not find firmware image %s\n", FW_FNAME);
		return (ENOENT);
	} else
		device_printf(sc->dev, "installing firmware on card\n");
	status = t3_load_fw(sc, (const uint8_t *)fw->data, fw->datasize);

	if (status != 0) {
		device_printf(sc->dev, "failed to install firmware: %d\n",
		    status);
	} else {
		t3_get_fw_version(sc, &vers);
		snprintf(&sc->fw_version[0], sizeof(sc->fw_version), "%d.%d.%d",
		    G_FW_VERSION_MAJOR(vers), G_FW_VERSION_MINOR(vers),
		    G_FW_VERSION_MICRO(vers));
	}

	firmware_put(fw, FIRMWARE_UNLOAD);

	return (status);	
}