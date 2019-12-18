#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct uuid {int dummy; } ;
typedef  struct uuid u_char ;
struct TYPE_6__ {int db_offset; int conf_size; int /*<<< orphan*/  dg_guid; int /*<<< orphan*/  dg_name; } ;
struct TYPE_5__ {int last_seq; int size; } ;
struct TYPE_4__ {int conf_offset; } ;
struct ldm_db {TYPE_3__ ph; TYPE_2__ dh; TYPE_1__ th; } ;
struct g_provider {int sectorsize; int /*<<< orphan*/  name; } ;
struct g_consumer {struct g_provider* provider; } ;
typedef  int /*<<< orphan*/  dg_guid ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int LDM_DB_DGGUID_OFF ; 
 int LDM_DB_DGNAME_OFF ; 
 int LDM_DB_LASTSEQ_OFF ; 
 int LDM_DB_SIZE_OFF ; 
 int LDM_DB_STATUS_OFF ; 
 int LDM_DB_VERSION_OFF ; 
 int /*<<< orphan*/  LDM_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LDM_DUMP (struct uuid*,int) ; 
 int /*<<< orphan*/ * LDM_VMDB_SIGN ; 
 int be16dec (struct uuid*) ; 
 void* be32dec (struct uuid*) ; 
 int /*<<< orphan*/  g_free (struct uuid*) ; 
 struct uuid* g_read_data (struct g_consumer*,int,int,int*) ; 
 scalar_t__ memcmp (struct uuid*,int /*<<< orphan*/ *,int) ; 
 int parse_uuid (struct uuid*,struct uuid*) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (struct uuid*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ldm_vmdbhdr_check(struct ldm_db *db, struct g_consumer *cp)
{
	struct g_provider *pp;
	struct uuid dg_guid;
	uint64_t offset;
	uint32_t version;
	int error;
	u_char *buf;

	pp = cp->provider;
	offset = db->ph.db_offset + db->th.conf_offset;
	buf = g_read_data(cp, offset * pp->sectorsize, pp->sectorsize,
	    &error);
	if (buf == NULL) {
		LDM_DEBUG(0, "%s: failed to read VMDB header at "
		    "LBA %ju", pp->name, (uintmax_t)offset);
		return (error);
	}
	if (memcmp(buf, LDM_VMDB_SIGN, strlen(LDM_VMDB_SIGN)) != 0) {
		g_free(buf);
		LDM_DEBUG(0, "%s: failed to parse VMDB header at "
		    "LBA %ju", pp->name, (uintmax_t)offset);
		return (ENXIO);
	}
	/* Check version. */
	version = be32dec(buf + LDM_DB_VERSION_OFF);
	if (version != 0x4000A) {
		g_free(buf);
		LDM_DEBUG(0, "%s: unsupported VMDB version %u.%u",
		    pp->name, version >> 16, version & 0xFFFF);
		return (ENXIO);
	}
	/*
	 * Check VMDB update status:
	 *	1 - in a consistent state;
	 *	2 - in a creation phase;
	 *	3 - in a deletion phase;
	 */
	if (be16dec(buf + LDM_DB_STATUS_OFF) != 1) {
		g_free(buf);
		LDM_DEBUG(0, "%s: VMDB is not in a consistent state",
		    pp->name);
		return (ENXIO);
	}
	db->dh.last_seq = be32dec(buf + LDM_DB_LASTSEQ_OFF);
	db->dh.size = be32dec(buf + LDM_DB_SIZE_OFF);
	error = parse_uuid(buf + LDM_DB_DGGUID_OFF, &dg_guid);
	/* Compare disk group name and guid from VMDB and private headers */
	if (error != 0 || db->dh.size == 0 ||
	    pp->sectorsize % db->dh.size != 0 ||
	    strncmp(buf + LDM_DB_DGNAME_OFF, db->ph.dg_name, 31) != 0 ||
	    memcmp(&dg_guid, &db->ph.dg_guid, sizeof(dg_guid)) != 0 ||
	    db->dh.size * db->dh.last_seq >
	    db->ph.conf_size * pp->sectorsize) {
		LDM_DEBUG(0, "%s: invalid values in the VMDB header",
		    pp->name);
		LDM_DUMP(buf, pp->sectorsize);
		g_free(buf);
		return (EINVAL);
	}
	g_free(buf);
	return (0);
}