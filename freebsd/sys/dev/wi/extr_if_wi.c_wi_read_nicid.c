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
typedef  int /*<<< orphan*/  ver ;
typedef  char u_int16_t ;
struct wi_softc {size_t sc_firmware_type; int sc_nic_id; char* sc_nic_name; int sc_pri_firmware_ver; int sc_sta_firmware_ver; int /*<<< orphan*/  sc_dev; } ;
struct wi_card_ident {char* card_name; scalar_t__ card_id; size_t firm_type; } ;
typedef  int /*<<< orphan*/  ident ;

/* Variables and functions */
 size_t WI_INTERSIL ; 
 size_t WI_LUCENT ; 
 size_t WI_NOTYPE ; 
 int /*<<< orphan*/  WI_RID_CARD_ID ; 
 int /*<<< orphan*/  WI_RID_PRI_IDENTITY ; 
 int /*<<< orphan*/  WI_RID_STA_IDENTITY ; 
 int /*<<< orphan*/  WI_RID_SYMBOL_IDENTITY ; 
 size_t WI_SYMBOL ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int le16toh (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 struct wi_card_ident* wi_card_ident ; 
 char** wi_firmware_names ; 
 scalar_t__ wi_read_rid (struct wi_softc*,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void
wi_read_nicid(struct wi_softc *sc)
{
	struct wi_card_ident *id;
	char *p;
	int len;
	u_int16_t ver[4];

	/* getting chip identity */
	memset(ver, 0, sizeof(ver));
	len = sizeof(ver);
	wi_read_rid(sc, WI_RID_CARD_ID, ver, &len);

	sc->sc_firmware_type = WI_NOTYPE;
	sc->sc_nic_id = le16toh(ver[0]);
	for (id = wi_card_ident; id->card_name != NULL; id++) {
		if (sc->sc_nic_id == id->card_id) {
			sc->sc_nic_name = id->card_name;
			sc->sc_firmware_type = id->firm_type;
			break;
		}
	}
	if (sc->sc_firmware_type == WI_NOTYPE) {
		if (sc->sc_nic_id & 0x8000) {
			sc->sc_firmware_type = WI_INTERSIL;
			sc->sc_nic_name = "Unknown Prism chip";
		} else {
			sc->sc_firmware_type = WI_LUCENT;
			sc->sc_nic_name = "Unknown Lucent chip";
		}
	}
	if (bootverbose)
		device_printf(sc->sc_dev, "using %s\n", sc->sc_nic_name);

	/* get primary firmware version (Only Prism chips) */
	if (sc->sc_firmware_type != WI_LUCENT) {
		memset(ver, 0, sizeof(ver));
		len = sizeof(ver);
		wi_read_rid(sc, WI_RID_PRI_IDENTITY, ver, &len);
		sc->sc_pri_firmware_ver = le16toh(ver[2]) * 10000 +
		    le16toh(ver[3]) * 100 + le16toh(ver[1]);
	}

	/* get station firmware version */
	memset(ver, 0, sizeof(ver));
	len = sizeof(ver);
	wi_read_rid(sc, WI_RID_STA_IDENTITY, ver, &len);
	sc->sc_sta_firmware_ver = le16toh(ver[2]) * 10000 +
	    le16toh(ver[3]) * 100 + le16toh(ver[1]);
	if (sc->sc_firmware_type == WI_INTERSIL &&
	    (sc->sc_sta_firmware_ver == 10102 ||
	     sc->sc_sta_firmware_ver == 20102)) {
		char ident[12];
		memset(ident, 0, sizeof(ident));
		len = sizeof(ident);
		/* value should be the format like "V2.00-11" */
		if (wi_read_rid(sc, WI_RID_SYMBOL_IDENTITY, ident, &len) == 0 &&
		    *(p = (char *)ident) >= 'A' &&
		    p[2] == '.' && p[5] == '-' && p[8] == '\0') {
			sc->sc_firmware_type = WI_SYMBOL;
			sc->sc_sta_firmware_ver = (p[1] - '0') * 10000 +
			    (p[3] - '0') * 1000 + (p[4] - '0') * 100 +
			    (p[6] - '0') * 10 + (p[7] - '0');
		}
	}
	if (bootverbose) {
		device_printf(sc->sc_dev, "%s Firmware: ",
		    wi_firmware_names[sc->sc_firmware_type]);
		if (sc->sc_firmware_type != WI_LUCENT)	/* XXX */
			printf("Primary (%u.%u.%u), ",
			    sc->sc_pri_firmware_ver / 10000,
			    (sc->sc_pri_firmware_ver % 10000) / 100,
			    sc->sc_pri_firmware_ver % 100);
		printf("Station (%u.%u.%u)\n",
		    sc->sc_sta_firmware_ver / 10000,
		    (sc->sc_sta_firmware_ver % 10000) / 100,
		    sc->sc_sta_firmware_ver % 100);
	}
}