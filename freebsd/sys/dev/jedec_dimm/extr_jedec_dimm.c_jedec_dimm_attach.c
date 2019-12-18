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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct jedec_dimm_softc {int spd_addr; int tsod_addr; char const* type_str; char const* part_str; char const* serial_str; char const* slotid_str; int /*<<< orphan*/  capacity_mb; int /*<<< orphan*/  smbus; int /*<<< orphan*/  dev; } ;
typedef  enum dram_type { ____Placeholder_dram_type } dram_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
#define  DRAM_TYPE_DDR3_SDRAM 129 
#define  DRAM_TYPE_DDR4_SDRAM 128 
 int EINVAL ; 
 int JEDEC_DTI_TSOD ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SPD_LEN_DDR3_PARTNUM ; 
 int /*<<< orphan*/  SPD_LEN_DDR3_SERIAL ; 
 int /*<<< orphan*/  SPD_LEN_DDR4_PARTNUM ; 
 int /*<<< orphan*/  SPD_LEN_DDR4_SERIAL ; 
 int /*<<< orphan*/  SPD_OFFSET_DDR3_PARTNUM ; 
 int /*<<< orphan*/  SPD_OFFSET_DDR3_SERIAL ; 
 int /*<<< orphan*/  SPD_OFFSET_DDR3_TSOD_PRESENT ; 
 int /*<<< orphan*/  SPD_OFFSET_DDR4_PARTNUM ; 
 int /*<<< orphan*/  SPD_OFFSET_DDR4_SERIAL ; 
 int /*<<< orphan*/  SPD_OFFSET_DDR4_TSOD_PRESENT ; 
 int /*<<< orphan*/  SPD_OFFSET_DRAM_TYPE ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  TSOD_REG_DEV_REV ; 
 int /*<<< orphan*/  TSOD_REG_MANUFACTURER ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (struct jedec_dimm_softc*,int) ; 
 char* device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct jedec_dimm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int jedec_dimm_capacity (struct jedec_dimm_softc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jedec_dimm_dump (struct jedec_dimm_softc*,int) ; 
 int jedec_dimm_field_to_str (struct jedec_dimm_softc*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int jedec_dimm_readw_be (struct jedec_dimm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jedec_dimm_temp_sysctl ; 
 char* jedec_dimm_tsod_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 int smbus_get_addr (int /*<<< orphan*/ ) ; 
 int smbus_readb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snprintf (char const*,int,char*,...) ; 
 char const* strdup (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
jedec_dimm_attach(device_t dev)
{
	uint8_t byte;
	uint16_t devid;
	uint16_t partnum_len;
	uint16_t partnum_offset;
	uint16_t serial_len;
	uint16_t serial_offset;
	uint16_t tsod_present_offset;
	uint16_t vendorid;
	bool tsod_present;
	int rc;
	int new_desc_len;
	enum dram_type type;
	struct jedec_dimm_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *oid;
	struct sysctl_oid_list *children;
	const char *tsod_match;
	const char *slotid_str;
	char *new_desc;

	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	oid = device_get_sysctl_tree(dev);
	children = SYSCTL_CHILDREN(oid);

	bzero(sc, sizeof(*sc));
	sc->dev = dev;
	sc->smbus = device_get_parent(dev);
	sc->spd_addr = smbus_get_addr(dev);

	/* The TSOD address has a different DTI from the SPD address, but shares
	 * the LSA bits.
	 */
	sc->tsod_addr = JEDEC_DTI_TSOD | (sc->spd_addr & 0x0f);

	/* Read the DRAM type, and set the various offsets and lengths. */
	rc = smbus_readb(sc->smbus, sc->spd_addr, SPD_OFFSET_DRAM_TYPE, &byte);
	if (rc != 0) {
		device_printf(dev, "failed to read dram_type: %d\n", rc);
		goto out;
	}
	type = (enum dram_type) byte;
	switch (type) {
	case DRAM_TYPE_DDR3_SDRAM:
		(void) snprintf(sc->type_str, sizeof(sc->type_str), "DDR3");
		partnum_len = SPD_LEN_DDR3_PARTNUM;
		partnum_offset = SPD_OFFSET_DDR3_PARTNUM;
		serial_len = SPD_LEN_DDR3_SERIAL;
		serial_offset = SPD_OFFSET_DDR3_SERIAL;
		tsod_present_offset = SPD_OFFSET_DDR3_TSOD_PRESENT;
		break;
	case DRAM_TYPE_DDR4_SDRAM:
		(void) snprintf(sc->type_str, sizeof(sc->type_str), "DDR4");
		partnum_len = SPD_LEN_DDR4_PARTNUM;
		partnum_offset = SPD_OFFSET_DDR4_PARTNUM;
		serial_len = SPD_LEN_DDR4_SERIAL;
		serial_offset = SPD_OFFSET_DDR4_SERIAL;
		tsod_present_offset = SPD_OFFSET_DDR4_TSOD_PRESENT;
		break;
	default:
		device_printf(dev, "unsupported dram_type 0x%02x\n", type);
		rc = EINVAL;
		goto out;
	}

	if (bootverbose) {
		/* bootverbose debuggery is best-effort, so ignore the rc. */
		(void) jedec_dimm_dump(sc, type);
	}

	/* Read all the required info from the SPD. If any of it fails, error
	 * out without creating the sysctls.
	 */
	rc = jedec_dimm_capacity(sc, type, &sc->capacity_mb);
	if (rc != 0) {
		goto out;
	}

	rc = jedec_dimm_field_to_str(sc, sc->part_str, sizeof(sc->part_str),
	    partnum_offset, partnum_len, true);
	if (rc != 0) {
		goto out;
	}

	rc = jedec_dimm_field_to_str(sc, sc->serial_str, sizeof(sc->serial_str),
	    serial_offset, serial_len, false);
	if (rc != 0) {
		goto out;
	}

	/* The MSBit of the TSOD-presence byte reports whether or not the TSOD
	 * is in fact present. (While DDR3 and DDR4 don't explicitly require a
	 * TSOD, essentially all DDR3 and DDR4 DIMMs include one.) But, as
	 * discussed in [PR 235944], it turns out that some DIMMs claim to have
	 * a TSOD when they actually don't. (Or maybe the firmware blocks it?)
	 * <sigh>
	 * If the SPD data says the TSOD is present, try to read manufacturer
	 * and device info from it to confirm that it's a valid TSOD device.
	 * If the data is unreadable, just continue as if the TSOD isn't there.
	 * If the data was read successfully, see if it is a known TSOD device;
	 * it's okay if it isn't (tsod_match == NULL).
	 */
	rc = smbus_readb(sc->smbus, sc->spd_addr, tsod_present_offset, &byte);
	if (rc != 0) {
		device_printf(dev, "failed to read TSOD-present byte: %d\n",
		    rc);
		goto out;
	}
	if (byte & 0x80) {
		tsod_present = true;
		rc = jedec_dimm_readw_be(sc, TSOD_REG_MANUFACTURER, &vendorid);
		if (rc != 0) {
			device_printf(dev,
			    "failed to read TSOD Manufacturer ID\n");
			rc = 0;
			goto no_tsod;
		}
		rc = jedec_dimm_readw_be(sc, TSOD_REG_DEV_REV, &devid);
		if (rc != 0) {
			device_printf(dev, "failed to read TSOD Device ID\n");
			rc = 0;
			goto no_tsod;
		}

		tsod_match = jedec_dimm_tsod_match(vendorid, devid);
		if (bootverbose) {
			if (tsod_match == NULL) {
				device_printf(dev,
				    "Unknown TSOD Manufacturer and Device IDs,"
				    " 0x%x and 0x%x\n", vendorid, devid);
			} else {
				device_printf(dev,
				    "TSOD: %s\n", tsod_match);
			}
		}
	} else {
no_tsod:
		tsod_match = NULL;
		tsod_present = false;
	}

	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "type",
	    CTLFLAG_RD | CTLFLAG_MPSAFE, sc->type_str, 0,
	    "DIMM type");

	SYSCTL_ADD_UINT(ctx, children, OID_AUTO, "capacity",
	    CTLFLAG_RD | CTLFLAG_MPSAFE, NULL, sc->capacity_mb,
	    "DIMM capacity (MB)");

	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "part",
	    CTLFLAG_RD | CTLFLAG_MPSAFE, sc->part_str, 0,
	    "DIMM Part Number");

	SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "serial",
	    CTLFLAG_RD | CTLFLAG_MPSAFE, sc->serial_str, 0,
	    "DIMM Serial Number");

	/* Create the temperature sysctl IFF the TSOD is present and valid */
	if (tsod_present && (tsod_match != NULL)) {
		SYSCTL_ADD_PROC(ctx, children, OID_AUTO, "temp",
		    CTLTYPE_INT | CTLFLAG_RD | CTLFLAG_MPSAFE, dev, 0,
		    jedec_dimm_temp_sysctl, "IK", "DIMM temperature (deg C)");
	}

	/* If a "slotid" was hinted, add the sysctl for it. */
	if (resource_string_value(device_get_name(dev), device_get_unit(dev),
	    "slotid", &slotid_str) == 0) {
		if (slotid_str != NULL) {
			sc->slotid_str = strdup(slotid_str, M_DEVBUF);
			SYSCTL_ADD_STRING(ctx, children, OID_AUTO, "slotid",
			    CTLFLAG_RD | CTLFLAG_MPSAFE, sc->slotid_str, 0,
			    "DIMM Slot Identifier");
		}
	}

	/* If a TSOD type string or a slotid are present, add them to the
	 * device description.
	 */
	if ((tsod_match != NULL) || (sc->slotid_str != NULL)) {
		new_desc_len = strlen(device_get_desc(dev));
		if (tsod_match != NULL) {
			new_desc_len += strlen(tsod_match);
			new_desc_len += 4; /* " w/ " */
		}
		if (sc->slotid_str != NULL) {
			new_desc_len += strlen(sc->slotid_str);
			new_desc_len += 3; /* space + parens */
		}
		new_desc_len++; /* terminator */
		new_desc = malloc(new_desc_len, M_TEMP, (M_WAITOK | M_ZERO));
		(void) snprintf(new_desc, new_desc_len, "%s%s%s%s%s%s",
		    device_get_desc(dev),
		    (tsod_match ? " w/ " : ""),
		    (tsod_match ? tsod_match : ""),
		    (sc->slotid_str ? " (" : ""),
		    (sc->slotid_str ? sc->slotid_str : ""),
		    (sc->slotid_str ? ")" : ""));
		device_set_desc_copy(dev, new_desc);
		free(new_desc, M_TEMP);
	}

out:
	return (rc);
}