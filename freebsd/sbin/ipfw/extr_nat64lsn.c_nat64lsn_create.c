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
typedef  void* uint8_t ;
typedef  void* uint16_t ;
struct TYPE_3__ {int count; int objsize; int size; int /*<<< orphan*/  opheader; } ;
typedef  TYPE_1__ ipfw_obj_lheader ;
struct TYPE_4__ {int plen6; int plen4; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; void* states_chunks; void* st_icmp_ttl; void* st_udp_ttl; void* st_estab_ttl; void* st_close_ttl; void* st_syn_ttl; void* pg_delete_delay; void* nh_delete_delay; void* max_ports; void* jmaxlen; int /*<<< orphan*/  prefix6; int /*<<< orphan*/  prefix4; void* set; } ;
typedef  TYPE_2__ ipfw_nat64lsn_cfg ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_FW_NAT64LSN_CREATE ; 
 int NAT64LSN_HAS_PREFIX4 ; 
 int NAT64LSN_HAS_PREFIX6 ; 
 void* NAT64LSN_HOST_AGE ; 
 void* NAT64LSN_ICMP_AGE ; 
 void* NAT64LSN_JMAXLEN ; 
 void* NAT64LSN_MAX_PORTS ; 
 void* NAT64LSN_PG_AGE ; 
 void* NAT64LSN_TCP_EST_AGE ; 
 void* NAT64LSN_TCP_FIN_AGE ; 
 void* NAT64LSN_TCP_SYN_AGE ; 
 void* NAT64LSN_UDP_AGE ; 
 int /*<<< orphan*/  NAT64_ALLOW_PRIVATE ; 
 int /*<<< orphan*/  NAT64_LOG ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_HOST_DEL_AGE 143 
#define  TOK_ICMP_AGE 142 
#define  TOK_JMAXLEN 141 
#define  TOK_LOG 140 
#define  TOK_LOGOFF 139 
#define  TOK_MAX_PORTS 138 
#define  TOK_PG_DEL_AGE 137 
#define  TOK_PREFIX4 136 
#define  TOK_PREFIX6 135 
#define  TOK_PRIVATE 134 
#define  TOK_PRIVATEOFF 133 
#define  TOK_STATES_CHUNKS 132 
#define  TOK_TCP_CLOSE_AGE 131 
#define  TOK_TCP_EST_AGE 130 
#define  TOK_TCP_SYN_AGE 129 
#define  TOK_UDP_AGE 128 
 scalar_t__ do_set3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipfw_check_nat64prefix (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 void* nat64lsn_parse_int (char*,char*) ; 
 int /*<<< orphan*/  nat64lsn_parse_prefix (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nat64newcmds ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
nat64lsn_create(const char *name, uint8_t set, int ac, char **av)
{
	char buf[sizeof(ipfw_obj_lheader) + sizeof(ipfw_nat64lsn_cfg)];
	ipfw_nat64lsn_cfg *cfg;
	ipfw_obj_lheader *olh;
	int tcmd, flags;
	char *opt;

	memset(&buf, 0, sizeof(buf));
	olh = (ipfw_obj_lheader *)buf;
	cfg = (ipfw_nat64lsn_cfg *)(olh + 1);

	/* Some reasonable defaults */
	inet_pton(AF_INET6, "64:ff9b::", &cfg->prefix6);
	cfg->plen6 = 96;
	cfg->set = set;
	cfg->max_ports = NAT64LSN_MAX_PORTS;
	cfg->jmaxlen = NAT64LSN_JMAXLEN;
	cfg->nh_delete_delay = NAT64LSN_HOST_AGE;
	cfg->pg_delete_delay = NAT64LSN_PG_AGE;
	cfg->st_syn_ttl = NAT64LSN_TCP_SYN_AGE;
	cfg->st_estab_ttl = NAT64LSN_TCP_EST_AGE;
	cfg->st_close_ttl = NAT64LSN_TCP_FIN_AGE;
	cfg->st_udp_ttl = NAT64LSN_UDP_AGE;
	cfg->st_icmp_ttl = NAT64LSN_ICMP_AGE;
	flags = NAT64LSN_HAS_PREFIX6;
	while (ac > 0) {
		tcmd = get_token(nat64newcmds, *av, "option");
		opt = *av;
		ac--; av++;

		switch (tcmd) {
		case TOK_PREFIX4:
			NEED1("IPv4 prefix required");
			nat64lsn_parse_prefix(*av, AF_INET, &cfg->prefix4,
			    &cfg->plen4);
			flags |= NAT64LSN_HAS_PREFIX4;
			ac--; av++;
			break;
		case TOK_PREFIX6:
			NEED1("IPv6 prefix required");
			nat64lsn_parse_prefix(*av, AF_INET6, &cfg->prefix6,
			    &cfg->plen6);
			if (ipfw_check_nat64prefix(&cfg->prefix6,
			    cfg->plen6) != 0 &&
			    !IN6_IS_ADDR_UNSPECIFIED(&cfg->prefix6))
				errx(EX_USAGE, "Bad prefix6 %s", *av);

			ac--; av++;
			break;
		case TOK_JMAXLEN:
			NEED1("job queue length required");
			cfg->jmaxlen = nat64lsn_parse_int(*av, opt);
			ac--; av++;
			break;
		case TOK_MAX_PORTS:
			NEED1("Max per-user ports required");
			cfg->max_ports = nat64lsn_parse_int(*av, opt);
			ac--; av++;
			break;
		case TOK_HOST_DEL_AGE:
			NEED1("host delete delay required");
			cfg->nh_delete_delay = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_PG_DEL_AGE:
			NEED1("portgroup delete delay required");
			cfg->pg_delete_delay = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_TCP_SYN_AGE:
			NEED1("tcp syn age required");
			cfg->st_syn_ttl = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_TCP_CLOSE_AGE:
			NEED1("tcp close age required");
			cfg->st_close_ttl = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_TCP_EST_AGE:
			NEED1("tcp est age required");
			cfg->st_estab_ttl = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_UDP_AGE:
			NEED1("udp age required");
			cfg->st_udp_ttl = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_ICMP_AGE:
			NEED1("icmp age required");
			cfg->st_icmp_ttl = (uint16_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_STATES_CHUNKS:
			NEED1("number of chunks required");
			cfg->states_chunks = (uint8_t)nat64lsn_parse_int(
			    *av, opt);
			ac--; av++;
			break;
		case TOK_LOG:
			cfg->flags |= NAT64_LOG;
			break;
		case TOK_LOGOFF:
			cfg->flags &= ~NAT64_LOG;
			break;
		case TOK_PRIVATE:
			cfg->flags |= NAT64_ALLOW_PRIVATE;
			break;
		case TOK_PRIVATEOFF:
			cfg->flags &= ~NAT64_ALLOW_PRIVATE;
			break;
		}
	}

	/* Check validness */
	if ((flags & NAT64LSN_HAS_PREFIX4) != NAT64LSN_HAS_PREFIX4)
		errx(EX_USAGE, "prefix4 required");

	olh->count = 1;
	olh->objsize = sizeof(*cfg);
	olh->size = sizeof(buf);
	strlcpy(cfg->name, name, sizeof(cfg->name));
	if (do_set3(IP_FW_NAT64LSN_CREATE, &olh->opheader, sizeof(buf)) != 0)
		err(EX_OSERR, "nat64lsn instance creation failed");
}