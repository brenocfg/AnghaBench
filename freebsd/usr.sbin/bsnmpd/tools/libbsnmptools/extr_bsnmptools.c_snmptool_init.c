#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snmp_toolinfo {int /*<<< orphan*/ * passwd; int /*<<< orphan*/  filelist; int /*<<< orphan*/  flags; int /*<<< orphan*/ * mappings; scalar_t__ objects; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sec_name; int /*<<< orphan*/  priv_proto; int /*<<< orphan*/  auth_proto; } ;
struct TYPE_5__ {int /*<<< orphan*/  version; TYPE_1__ user; } ;

/* Variables and functions */
 int /*<<< orphan*/  IsoOrgDod_OID ; 
 size_t MAXSTR ; 
 int /*<<< orphan*/  SET_MAXREP (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNMP_AUTH_HMAC_MD5 ; 
 int /*<<< orphan*/  SNMP_AUTH_HMAC_SHA ; 
 int /*<<< orphan*/  SNMP_MAX_REPETITIONS ; 
 int /*<<< orphan*/  SNMP_PDU_GET ; 
 int /*<<< orphan*/  SNMP_PRIV_AES ; 
 int /*<<< orphan*/  SNMP_PRIV_DES ; 
 int /*<<< orphan*/  SNMP_V3 ; 
 scalar_t__ add_filename (struct snmp_toolinfo*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bsnmpd_defs ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct snmp_toolinfo*,int /*<<< orphan*/ ,int) ; 
 char* mibII_defs ; 
 TYPE_2__ snmp_client ; 
 int /*<<< orphan*/  snmp_client_init (TYPE_2__*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
snmptool_init(struct snmp_toolinfo *snmptoolctx)
{
	char *str;
	size_t slen;

	memset(snmptoolctx, 0, sizeof(struct snmp_toolinfo));
	snmptoolctx->objects = 0;
	snmptoolctx->mappings = NULL;
	snmptoolctx->flags = SNMP_PDU_GET;	/* XXX */
	SLIST_INIT(&snmptoolctx->filelist);
	snmp_client_init(&snmp_client);
	SET_MAXREP(snmptoolctx, SNMP_MAX_REPETITIONS);

	if (add_filename(snmptoolctx, bsnmpd_defs, &IsoOrgDod_OID, 0) < 0)
		warnx("Error adding file %s to list", bsnmpd_defs);

	if (add_filename(snmptoolctx, mibII_defs, &IsoOrgDod_OID, 0) < 0)
		warnx("Error adding file %s to list", mibII_defs);

	/* Read the environment */
	if ((str = getenv("SNMPAUTH")) != NULL) {
		slen = strlen(str);
		if (slen == strlen("md5") && strcasecmp(str, "md5") == 0)
			snmp_client.user.auth_proto = SNMP_AUTH_HMAC_MD5;
		else if (slen == strlen("sha")&& strcasecmp(str, "sha") == 0)
			snmp_client.user.auth_proto = SNMP_AUTH_HMAC_SHA;
		else if (slen != 0)
			warnx("Bad authentication type - %s in SNMPAUTH", str);
	}

	if ((str = getenv("SNMPPRIV")) != NULL) {
		slen = strlen(str);
		if (slen == strlen("des") && strcasecmp(str, "des") == 0)
			snmp_client.user.priv_proto = SNMP_PRIV_DES;
		else if (slen == strlen("aes")&& strcasecmp(str, "aes") == 0)
			snmp_client.user.priv_proto = SNMP_PRIV_AES;
		else if (slen != 0)
			warnx("Bad privacy type - %s in SNMPPRIV", str);
	}

	if ((str = getenv("SNMPUSER")) != NULL) {
		if ((slen = strlen(str)) > sizeof(snmp_client.user.sec_name)) {
			warnx("Username too long - %s in SNMPUSER", str);
			return (-1);
		}
		if (slen > 0) {
			strlcpy(snmp_client.user.sec_name, str,
			    sizeof(snmp_client.user.sec_name));
			snmp_client.version = SNMP_V3;
		}
	}

	if ((str = getenv("SNMPPASSWD")) != NULL) {
		if ((slen = strlen(str)) > MAXSTR)
			slen = MAXSTR - 1;
		if ((snmptoolctx->passwd = malloc(slen + 1)) == NULL) {
			warn("malloc() failed");
			return (-1);
		}
		if (slen > 0)
			strlcpy(snmptoolctx->passwd, str, slen + 1);
	}

	return (0);
}