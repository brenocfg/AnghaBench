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
typedef  void* uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  opheader; int /*<<< orphan*/  ntlv; } ;
typedef  TYPE_1__ ipfw_obj_header ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  states_chunks; void* st_icmp_ttl; void* st_udp_ttl; void* st_estab_ttl; void* st_close_ttl; void* st_syn_ttl; void* pg_delete_delay; void* nh_delete_delay; void* jmaxlen; void* max_ports; } ;
typedef  TYPE_2__ ipfw_nat64lsn_cfg ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  IP_FW_NAT64LSN_CONFIG ; 
 int /*<<< orphan*/  NAT64_ALLOW_PRIVATE ; 
 int /*<<< orphan*/  NAT64_LOG ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_HOST_DEL_AGE 141 
#define  TOK_ICMP_AGE 140 
#define  TOK_JMAXLEN 139 
#define  TOK_LOG 138 
#define  TOK_LOGOFF 137 
#define  TOK_MAX_PORTS 136 
#define  TOK_PG_DEL_AGE 135 
#define  TOK_PRIVATE 134 
#define  TOK_PRIVATEOFF 133 
#define  TOK_STATES_CHUNKS 132 
#define  TOK_TCP_CLOSE_AGE 131 
#define  TOK_TCP_EST_AGE 130 
#define  TOK_TCP_SYN_AGE 129 
#define  TOK_UDP_AGE 128 
 scalar_t__ do_get3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ do_set3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nat64lsn_fill_ntlv (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 void* nat64lsn_parse_int (char*,char*) ; 
 int /*<<< orphan*/  nat64newcmds ; 

__attribute__((used)) static void
nat64lsn_config(const char *name, uint8_t set, int ac, char **av)
{
	char buf[sizeof(ipfw_obj_header) + sizeof(ipfw_nat64lsn_cfg)];
	ipfw_nat64lsn_cfg *cfg;
	ipfw_obj_header *oh;
	size_t sz;
	char *opt;
	int tcmd;

	if (ac == 0)
		errx(EX_USAGE, "config options required");
	memset(&buf, 0, sizeof(buf));
	oh = (ipfw_obj_header *)buf;
	cfg = (ipfw_nat64lsn_cfg *)(oh + 1);
	sz = sizeof(buf);

	nat64lsn_fill_ntlv(&oh->ntlv, name, set);
	if (do_get3(IP_FW_NAT64LSN_CONFIG, &oh->opheader, &sz) != 0)
		err(EX_OSERR, "failed to get config for instance %s", name);

	while (ac > 0) {
		tcmd = get_token(nat64newcmds, *av, "option");
		opt = *av;
		ac--; av++;

		switch (tcmd) {
		case TOK_MAX_PORTS:
			NEED1("Max per-user ports required");
			cfg->max_ports = nat64lsn_parse_int(*av, opt);
			ac--; av++;
			break;
		case TOK_JMAXLEN:
			NEED1("job queue length required");
			cfg->jmaxlen = nat64lsn_parse_int(*av, opt);
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
		default:
			errx(EX_USAGE, "Can't change %s option", opt);
		}
	}

	if (do_set3(IP_FW_NAT64LSN_CONFIG, &oh->opheader, sizeof(buf)) != 0)
		err(EX_OSERR, "nat64lsn instance configuration failed");
}