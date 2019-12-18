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
struct firmware {int /*<<< orphan*/  data; int /*<<< orphan*/  datasize; } ;
struct adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 char* TPSRAM_NAME ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 
 int t3_check_tpsram (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_set_proto_sram (struct adapter*,int /*<<< orphan*/ ) ; 
 char t3rev2char (struct adapter*) ; 
 int /*<<< orphan*/  update_tpeeprom (struct adapter*) ; 

__attribute__((used)) static int
update_tpsram(struct adapter *adap)
{
	const struct firmware *tpsram;
	int ret;
	char rev, name[32];

	rev = t3rev2char(adap);
	snprintf(name, sizeof(name), TPSRAM_NAME, rev);

	update_tpeeprom(adap);

	tpsram = firmware_get(name);
	if (tpsram == NULL){
		device_printf(adap->dev, "could not load TP SRAM\n");
		return (EINVAL);
	} else
		device_printf(adap->dev, "updating TP SRAM\n");
	
	ret = t3_check_tpsram(adap, tpsram->data, tpsram->datasize);
	if (ret)
		goto release_tpsram;	

	ret = t3_set_proto_sram(adap, tpsram->data);
	if (ret)
		device_printf(adap->dev, "loading protocol SRAM failed\n");

release_tpsram:
	firmware_put(tpsram, FIRMWARE_UNLOAD);
	
	return ret;
}