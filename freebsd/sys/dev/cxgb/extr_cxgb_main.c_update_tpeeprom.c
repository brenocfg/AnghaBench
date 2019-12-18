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
typedef  int /*<<< orphan*/  uint32_t ;
struct firmware {int datasize; int /*<<< orphan*/  data; } ;
struct adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/ * port; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 unsigned int G_TP_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 unsigned int G_TP_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 char* TPEEPROM_NAME ; 
 int TP_SRAM_LEN ; 
 int /*<<< orphan*/  TP_SRAM_OFFSET ; 
 unsigned int TP_VERSION_MAJOR ; 
 int /*<<< orphan*/  TP_VERSION_MICRO ; 
 unsigned int TP_VERSION_MINOR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 int set_eeprom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 
 int t3_check_tpsram (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_seeprom_read (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char t3rev2char (struct adapter*) ; 

__attribute__((used)) static void
update_tpeeprom(struct adapter *adap)
{
	const struct firmware *tpeeprom;

	uint32_t version;
	unsigned int major, minor;
	int ret, len;
	char rev, name[32];

	t3_seeprom_read(adap, TP_SRAM_OFFSET, &version);

	major = G_TP_VERSION_MAJOR(version);
	minor = G_TP_VERSION_MINOR(version);
	if (major == TP_VERSION_MAJOR  && minor == TP_VERSION_MINOR)
		return; 

	rev = t3rev2char(adap);
	snprintf(name, sizeof(name), TPEEPROM_NAME, rev);

	tpeeprom = firmware_get(name);
	if (tpeeprom == NULL) {
		device_printf(adap->dev,
			      "could not load TP EEPROM: unable to load %s\n",
			      name);
		return;
	}

	len = tpeeprom->datasize - 4;
	
	ret = t3_check_tpsram(adap, tpeeprom->data, tpeeprom->datasize);
	if (ret)
		goto release_tpeeprom;

	if (len != TP_SRAM_LEN) {
		device_printf(adap->dev,
			      "%s length is wrong len=%d expected=%d\n", name,
			      len, TP_SRAM_LEN);
		return;
	}
	
	ret = set_eeprom(&adap->port[0], tpeeprom->data, tpeeprom->datasize,
	    TP_SRAM_OFFSET);
	
	if (!ret) {
		device_printf(adap->dev,
			"Protocol SRAM image updated in EEPROM to %d.%d.%d\n",
			 TP_VERSION_MAJOR, TP_VERSION_MINOR, TP_VERSION_MICRO);
	} else 
		device_printf(adap->dev,
			      "Protocol SRAM image update in EEPROM failed\n");

release_tpeeprom:
	firmware_put(tpeeprom, FIRMWARE_UNLOAD);
	
	return;
}