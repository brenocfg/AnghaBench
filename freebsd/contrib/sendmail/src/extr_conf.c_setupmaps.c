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
typedef  int /*<<< orphan*/  STAB ;

/* Variables and functions */
 int DB_VERSION_MAJOR ; 
 int DB_VERSION_MINOR ; 
 int /*<<< orphan*/  DB_VERSION_PATCH ; 
 int /*<<< orphan*/  MAPDEF (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MCF_ALIASOK ; 
 int MCF_ALIASONLY ; 
 int MCF_NOTPERSIST ; 
 int MCF_OPTFILE ; 
 int MCF_REBUILDABLE ; 
 int /*<<< orphan*/  arith_map_lookup ; 
 int /*<<< orphan*/  arpa_map_lookup ; 
 int /*<<< orphan*/  bestmx_map_lookup ; 
 int /*<<< orphan*/  bogus_map_lookup ; 
 int /*<<< orphan*/  bt_map_open ; 
 int /*<<< orphan*/  db_map_close ; 
 int /*<<< orphan*/  db_map_lookup ; 
 int /*<<< orphan*/  db_map_store ; 
 int /*<<< orphan*/  db_version (int*,int*,int*) ; 
 int /*<<< orphan*/  dequote_init ; 
 int /*<<< orphan*/  dequote_map ; 
 int /*<<< orphan*/  dns_map_init ; 
 int /*<<< orphan*/  dns_map_lookup ; 
 int /*<<< orphan*/  dns_map_open ; 
 int /*<<< orphan*/  dns_map_parseargs ; 
 int /*<<< orphan*/  dprintf_map_lookup ; 
 int /*<<< orphan*/  dprintf_map_parseargs ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  hash_map_open ; 
 int /*<<< orphan*/  hes_map_close ; 
 int /*<<< orphan*/  hes_map_lookup ; 
 int /*<<< orphan*/  hes_map_open ; 
 int /*<<< orphan*/  host_map_init ; 
 int /*<<< orphan*/  host_map_lookup ; 
 int /*<<< orphan*/  impl_map_close ; 
 int /*<<< orphan*/  impl_map_lookup ; 
 int /*<<< orphan*/  impl_map_open ; 
 int /*<<< orphan*/  impl_map_store ; 
 int /*<<< orphan*/  ldapmap_close ; 
 int /*<<< orphan*/  ldapmap_lookup ; 
 int /*<<< orphan*/  ldapmap_open ; 
 int /*<<< orphan*/  ldapmap_parseargs ; 
 int /*<<< orphan*/  macro_map_lookup ; 
 int /*<<< orphan*/  map_parseargs ; 
 int /*<<< orphan*/  ndbm_map_close ; 
 int /*<<< orphan*/  ndbm_map_lookup ; 
 int /*<<< orphan*/  ndbm_map_open ; 
 int /*<<< orphan*/  ndbm_map_store ; 
 int /*<<< orphan*/  ni_map_lookup ; 
 int /*<<< orphan*/  ni_map_open ; 
 int /*<<< orphan*/  nis_map_lookup ; 
 int /*<<< orphan*/  nis_map_open ; 
 int /*<<< orphan*/  nisplus_map_lookup ; 
 int /*<<< orphan*/  nisplus_map_open ; 
 int /*<<< orphan*/  nsd_map_lookup ; 
 int /*<<< orphan*/  null_map_close ; 
 int /*<<< orphan*/  null_map_lookup ; 
 int /*<<< orphan*/  null_map_open ; 
 int /*<<< orphan*/  null_map_store ; 
 int /*<<< orphan*/  ph_map_close ; 
 int /*<<< orphan*/  ph_map_lookup ; 
 int /*<<< orphan*/  ph_map_open ; 
 int /*<<< orphan*/  ph_map_parseargs ; 
 int /*<<< orphan*/  prog_map_lookup ; 
 int /*<<< orphan*/  regex_map_init ; 
 int /*<<< orphan*/  regex_map_lookup ; 
 int /*<<< orphan*/  seq_map_lookup ; 
 int /*<<< orphan*/  seq_map_parse ; 
 int /*<<< orphan*/  seq_map_store ; 
 int /*<<< orphan*/  socket_map_close ; 
 int /*<<< orphan*/  socket_map_lookup ; 
 int /*<<< orphan*/  socket_map_open ; 
 int /*<<< orphan*/  stab_map_lookup ; 
 int /*<<< orphan*/  stab_map_open ; 
 int /*<<< orphan*/  stab_map_store ; 
 int /*<<< orphan*/  switch_map_open ; 
 int /*<<< orphan*/  syserr (char*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  syslog_map_lookup ; 
 int /*<<< orphan*/  syslog_map_parseargs ; 
 scalar_t__ tTd (int,int) ; 
 int /*<<< orphan*/  text_map_lookup ; 
 int /*<<< orphan*/  text_map_open ; 
 int /*<<< orphan*/  udb_map_lookup ; 
 int /*<<< orphan*/  user_map_lookup ; 
 int /*<<< orphan*/  user_map_open ; 

__attribute__((used)) static void
setupmaps()
{
	register STAB *s;

#if NEWDB
# if DB_VERSION_MAJOR > 1
	int major_v, minor_v, patch_v;

	(void) db_version(&major_v, &minor_v, &patch_v);
	if (major_v != DB_VERSION_MAJOR || minor_v != DB_VERSION_MINOR)
	{
		errno = 0;
		syserr("Berkeley DB version mismatch: compiled against %d.%d.%d, run-time linked against %d.%d.%d",
		  DB_VERSION_MAJOR, DB_VERSION_MINOR, DB_VERSION_PATCH,
		  major_v, minor_v, patch_v);
	}
# endif /* DB_VERSION_MAJOR > 1 */

	MAPDEF("hash", ".db", MCF_ALIASOK|MCF_REBUILDABLE,
		map_parseargs, hash_map_open, db_map_close,
		db_map_lookup, db_map_store);

	MAPDEF("btree", ".db", MCF_ALIASOK|MCF_REBUILDABLE,
		map_parseargs, bt_map_open, db_map_close,
		db_map_lookup, db_map_store);
#endif /* NEWDB */

#if NDBM
	MAPDEF("dbm", ".dir", MCF_ALIASOK|MCF_REBUILDABLE,
		map_parseargs, ndbm_map_open, ndbm_map_close,
		ndbm_map_lookup, ndbm_map_store);
#endif /* NDBM */

#if NIS
	MAPDEF("nis", NULL, MCF_ALIASOK,
		map_parseargs, nis_map_open, null_map_close,
		nis_map_lookup, null_map_store);
#endif /* NIS */

#if NISPLUS
	MAPDEF("nisplus", NULL, MCF_ALIASOK,
		map_parseargs, nisplus_map_open, null_map_close,
		nisplus_map_lookup, null_map_store);
#endif /* NISPLUS */

#if LDAPMAP
	MAPDEF("ldap", NULL, MCF_ALIASOK|MCF_NOTPERSIST,
		ldapmap_parseargs, ldapmap_open, ldapmap_close,
		ldapmap_lookup, null_map_store);
#endif /* LDAPMAP */

#if PH_MAP
	MAPDEF("ph", NULL, MCF_NOTPERSIST,
		ph_map_parseargs, ph_map_open, ph_map_close,
		ph_map_lookup, null_map_store);
#endif /* PH_MAP */

#if MAP_NSD
	/* IRIX 6.5 nsd support */
	MAPDEF("nsd", NULL, MCF_ALIASOK,
	       map_parseargs, null_map_open, null_map_close,
	       nsd_map_lookup, null_map_store);
#endif /* MAP_NSD */

#if HESIOD
	MAPDEF("hesiod", NULL, MCF_ALIASOK|MCF_ALIASONLY,
		map_parseargs, hes_map_open, hes_map_close,
		hes_map_lookup, null_map_store);
#endif /* HESIOD */

#if NETINFO
	MAPDEF("netinfo", NULL, MCF_ALIASOK,
		map_parseargs, ni_map_open, null_map_close,
		ni_map_lookup, null_map_store);
#endif /* NETINFO */

#if 0
	MAPDEF("dns", NULL, 0,
		dns_map_init, null_map_open, null_map_close,
		dns_map_lookup, null_map_store);
#endif /* 0 */

#if NAMED_BIND
# if DNSMAP
#  if _FFR_DNSMAP_ALIASABLE
	MAPDEF("dns", NULL, MCF_ALIASOK,
	       dns_map_parseargs, dns_map_open, null_map_close,
	       dns_map_lookup, null_map_store);
#  else /* _FFR_DNSMAP_ALIASABLE */
	MAPDEF("dns", NULL, 0,
	       dns_map_parseargs, dns_map_open, null_map_close,
	       dns_map_lookup, null_map_store);
#  endif /* _FFR_DNSMAP_ALIASABLE */
# endif /* DNSMAP */
#endif /* NAMED_BIND */

#if NAMED_BIND
	/* best MX DNS lookup */
	MAPDEF("bestmx", NULL, MCF_OPTFILE,
		map_parseargs, null_map_open, null_map_close,
		bestmx_map_lookup, null_map_store);
#endif /* NAMED_BIND */

	MAPDEF("host", NULL, 0,
		host_map_init, null_map_open, null_map_close,
		host_map_lookup, null_map_store);

	MAPDEF("text", NULL, MCF_ALIASOK,
		map_parseargs, text_map_open, null_map_close,
		text_map_lookup, null_map_store);

	MAPDEF("stab", NULL, MCF_ALIASOK|MCF_ALIASONLY,
		map_parseargs, stab_map_open, null_map_close,
		stab_map_lookup, stab_map_store);

	MAPDEF("implicit", NULL, MCF_ALIASOK|MCF_ALIASONLY|MCF_REBUILDABLE,
		map_parseargs, impl_map_open, impl_map_close,
		impl_map_lookup, impl_map_store);

	/* access to system passwd file */
	MAPDEF("user", NULL, MCF_OPTFILE,
		map_parseargs, user_map_open, null_map_close,
		user_map_lookup, null_map_store);

	/* dequote map */
	MAPDEF("dequote", NULL, 0,
		dequote_init, null_map_open, null_map_close,
		dequote_map, null_map_store);

#if MAP_REGEX
	MAPDEF("regex", NULL, 0,
		regex_map_init, null_map_open, null_map_close,
		regex_map_lookup, null_map_store);
#endif /* MAP_REGEX */

#if USERDB
	/* user database */
	MAPDEF("userdb", ".db", 0,
		map_parseargs, null_map_open, null_map_close,
		udb_map_lookup, null_map_store);
#endif /* USERDB */

	/* arbitrary programs */
	MAPDEF("program", NULL, MCF_ALIASOK,
		map_parseargs, null_map_open, null_map_close,
		prog_map_lookup, null_map_store);

	/* sequenced maps */
	MAPDEF("sequence", NULL, MCF_ALIASOK,
		seq_map_parse, null_map_open, null_map_close,
		seq_map_lookup, seq_map_store);

	/* switched interface to sequenced maps */
	MAPDEF("switch", NULL, MCF_ALIASOK,
		map_parseargs, switch_map_open, null_map_close,
		seq_map_lookup, seq_map_store);

	/* null map lookup -- really for internal use only */
	MAPDEF("null", NULL, MCF_ALIASOK|MCF_OPTFILE,
		map_parseargs, null_map_open, null_map_close,
		null_map_lookup, null_map_store);

	/* syslog map -- logs information to syslog */
	MAPDEF("syslog", NULL, 0,
		syslog_map_parseargs, null_map_open, null_map_close,
		syslog_map_lookup, null_map_store);

	/* macro storage map -- rulesets can set macros */
	MAPDEF("macro", NULL, 0,
		dequote_init, null_map_open, null_map_close,
		macro_map_lookup, null_map_store);

	/* arithmetic map -- add/subtract/compare */
	MAPDEF("arith", NULL, 0,
		dequote_init, null_map_open, null_map_close,
		arith_map_lookup, null_map_store);

	/* "arpa" map -- IP -> arpa */
	MAPDEF("arpa", NULL, 0,
		dequote_init, null_map_open, null_map_close,
		arpa_map_lookup, null_map_store);

#if SOCKETMAP
	/* arbitrary daemons */
	MAPDEF("socket", NULL, MCF_ALIASOK,
		map_parseargs, socket_map_open, socket_map_close,
		socket_map_lookup, null_map_store);
#endif /* SOCKETMAP */

#if _FFR_DPRINTF_MAP
	/* dprintf map -- logs information to syslog */
	MAPDEF("dprintf", NULL, 0,
		dprintf_map_parseargs, null_map_open, null_map_close,
		dprintf_map_lookup, null_map_store);
#endif /* _FFR_DPRINTF_MAP */

	if (tTd(38, 2))
	{
		/* bogus map -- always return tempfail */
		MAPDEF("bogus",	NULL, MCF_ALIASOK|MCF_OPTFILE,
		       map_parseargs, null_map_open, null_map_close,
		       bogus_map_lookup, null_map_store);
	}
}