#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct in6_addr {int dummy; } ;
struct TYPE_3__ {int count; int objsize; int size; int /*<<< orphan*/  opheader; } ;
typedef  TYPE_1__ ipfw_obj_lheader ;
struct TYPE_4__ {int flags; int plen; int /*<<< orphan*/  name; int /*<<< orphan*/  external; int /*<<< orphan*/  internal; int /*<<< orphan*/  if_name; int /*<<< orphan*/  set; } ;
typedef  TYPE_2__ ipfw_nptv6_cfg ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  APPLY_MASK (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IP_FW_NPTV6_CREATE ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
 int NPTV6_DYNAMIC_PREFIX ; 
 int NPTV6_HAS_EXTPREFIX ; 
 int NPTV6_HAS_INTPREFIX ; 
 int NPTV6_HAS_PREFIXLEN ; 
#define  TOK_EXTIF 131 
#define  TOK_EXTPREFIX 130 
#define  TOK_INTPREFIX 129 
#define  TOK_PREFIXLEN 128 
 scalar_t__ do_set3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n2mask (struct in6_addr*,int) ; 
 int /*<<< orphan*/  nptv6_parse_prefix (char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nptv6newcmds ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  warnx (char*,int,int,int) ; 

__attribute__((used)) static void
nptv6_create(const char *name, uint8_t set, int ac, char *av[])
{
	char buf[sizeof(ipfw_obj_lheader) + sizeof(ipfw_nptv6_cfg)];
	struct in6_addr mask;
	ipfw_nptv6_cfg *cfg;
	ipfw_obj_lheader *olh;
	int tcmd, flags, plen;
	char *p = "\0";

	plen = 0;
	memset(buf, 0, sizeof(buf));
	olh = (ipfw_obj_lheader *)buf;
	cfg = (ipfw_nptv6_cfg *)(olh + 1);
	cfg->set = set;
	flags = 0;
	while (ac > 0) {
		tcmd = get_token(nptv6newcmds, *av, "option");
		ac--; av++;

		switch (tcmd) {
		case TOK_INTPREFIX:
			NEED1("IPv6 prefix required");
			nptv6_parse_prefix(*av, &cfg->internal, &plen);
			flags |= NPTV6_HAS_INTPREFIX;
			if (plen > 0)
				goto check_prefix;
			ac--; av++;
			break;
		case TOK_EXTPREFIX:
			if (flags & NPTV6_HAS_EXTPREFIX)
				errx(EX_USAGE,
				    "Only one ext_prefix or ext_if allowed");
			NEED1("IPv6 prefix required");
			nptv6_parse_prefix(*av, &cfg->external, &plen);
			flags |= NPTV6_HAS_EXTPREFIX;
			if (plen > 0)
				goto check_prefix;
			ac--; av++;
			break;
		case TOK_EXTIF:
			if (flags & NPTV6_HAS_EXTPREFIX)
				errx(EX_USAGE,
				    "Only one ext_prefix or ext_if allowed");
			NEED1("Interface name required");
			if (strlen(*av) >= sizeof(cfg->if_name))
				errx(EX_USAGE, "Invalid interface name");
			flags |= NPTV6_HAS_EXTPREFIX;
			cfg->flags |= NPTV6_DYNAMIC_PREFIX;
			strncpy(cfg->if_name, *av, sizeof(cfg->if_name));
			ac--; av++;
			break;
		case TOK_PREFIXLEN:
			NEED1("IPv6 prefix length required");
			plen = strtol(*av, &p, 10);
check_prefix:
			if (*p != '\0' || plen < 8 || plen > 64)
				errx(EX_USAGE, "wrong prefix length: %s", *av);
			/* RFC 6296 Sec. 3.1 */
			if (cfg->plen > 0 && cfg->plen != plen) {
				warnx("Prefix length mismatch (%d vs %d).  "
				    "It was extended up to %d",
				    cfg->plen, plen, MAX(plen, cfg->plen));
				plen = MAX(plen, cfg->plen);
			}
			cfg->plen = plen;
			flags |= NPTV6_HAS_PREFIXLEN;
			ac--; av++;
			break;
		}
	}

	/* Check validness */
	if ((flags & NPTV6_HAS_INTPREFIX) != NPTV6_HAS_INTPREFIX)
		errx(EX_USAGE, "int_prefix required");
	if ((flags & NPTV6_HAS_EXTPREFIX) != NPTV6_HAS_EXTPREFIX)
		errx(EX_USAGE, "ext_prefix or ext_if required");
	if ((flags & NPTV6_HAS_PREFIXLEN) != NPTV6_HAS_PREFIXLEN)
		errx(EX_USAGE, "prefixlen required");

	n2mask(&mask, cfg->plen);
	APPLY_MASK(&cfg->internal, &mask);
	if ((cfg->flags & NPTV6_DYNAMIC_PREFIX) == 0)
		APPLY_MASK(&cfg->external, &mask);

	olh->count = 1;
	olh->objsize = sizeof(*cfg);
	olh->size = sizeof(buf);
	strlcpy(cfg->name, name, sizeof(cfg->name));
	if (do_set3(IP_FW_NPTV6_CREATE, &olh->opheader, sizeof(buf)) != 0)
		err(EX_OSERR, "nptv6 instance creation failed");
}