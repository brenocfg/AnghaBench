#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct TYPE_2__ {int len; int subtype; } ;
struct dn_extra_parms {int* par; int /*<<< orphan*/  name; int /*<<< orphan*/  nr; TYPE_1__ oid; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int CODEL_ECN_ENABLED ; 
 int /*<<< orphan*/  DN_API_VERSION ; 
#define  DN_AQM_PARAMS 129 
 int /*<<< orphan*/  DN_CMD_GET ; 
#define  DN_SCH_PARAMS 128 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  IP_DUMMYNET3 ; 
 int PIE_CAPDROP_ENABLED ; 
 int PIE_DEPRATEEST_ENABLED ; 
 int PIE_DERAND_ENABLED ; 
 int PIE_ECN_ENABLED ; 
 int PIE_ON_OFF_MODE_ENABLED ; 
 scalar_t__ PIE_SCALE ; 
 int do_cmd (int /*<<< orphan*/ ,struct dn_extra_parms*,uintptr_t) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct dn_extra_parms*) ; 
 int /*<<< orphan*/  memset (struct dn_extra_parms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_fill (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dn_extra_parms* safe_calloc (int,int) ; 
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  us_to_time (int,char*) ; 

void
get_extra_parms(uint32_t nr, char *out, int subtype)
{ 
	struct dn_extra_parms *ep;
	int ret;
	char strt1[15], strt2[15], strt3[15];
	u_int l;

	/* prepare the request */
	l = sizeof(struct dn_extra_parms);
	ep = safe_calloc(1, l);
	memset(ep, 0, sizeof(*ep));
	*out = '\0';

	oid_fill(&ep->oid, l, DN_CMD_GET, DN_API_VERSION);
	ep->oid.len = l;
	ep->oid.subtype = subtype;
	ep->nr = nr;

	ret = do_cmd(-IP_DUMMYNET3, ep, (uintptr_t)&l);
	if (ret) {
		free(ep);
		errx(EX_DATAERR, "Error getting extra parameters\n");
	}

	switch (subtype) {
	case DN_AQM_PARAMS:
		if( !strcasecmp(ep->name, "codel")) {
			us_to_time(ep->par[0], strt1);
			us_to_time(ep->par[1], strt2);
			l = sprintf(out, " AQM CoDel target %s interval %s",
				strt1, strt2);
			if (ep->par[2] & CODEL_ECN_ENABLED)
				l = sprintf(out + l, " ECN");
			else
				l += sprintf(out + l, " NoECN");
		} else if( !strcasecmp(ep->name, "pie")) {
			us_to_time(ep->par[0], strt1);
			us_to_time(ep->par[1], strt2);
			us_to_time(ep->par[2], strt3);
			l = sprintf(out, " AQM type PIE target %s tupdate %s alpha "
					"%g beta %g max_burst %s max_ecnth %.3g",
					strt1,
					strt2,
					ep->par[4] / (float) PIE_SCALE,
					ep->par[5] / (float) PIE_SCALE,
					strt3,
					ep->par[3] / (float) PIE_SCALE
				);
				
			if (ep->par[6] & PIE_ECN_ENABLED)
				l += sprintf(out + l, " ECN");
			else
				l += sprintf(out + l, " NoECN");
			if (ep->par[6] & PIE_CAPDROP_ENABLED)
				l += sprintf(out + l, " CapDrop");
			else
				l += sprintf(out + l, " NoCapDrop");
			if (ep->par[6] & PIE_ON_OFF_MODE_ENABLED)
				l += sprintf(out + l, " OnOff");
			if (ep->par[6] & PIE_DEPRATEEST_ENABLED)
				l += sprintf(out + l, " DRE");
			else
				l += sprintf(out + l, " TS");
			if (ep->par[6] & PIE_DERAND_ENABLED)
				l += sprintf(out + l, " Derand");
			else
				l += sprintf(out + l, " NoDerand");
		}
		break;

	case	DN_SCH_PARAMS:
		if (!strcasecmp(ep->name,"FQ_CODEL")) {
			us_to_time(ep->par[0], strt1);
			us_to_time(ep->par[1], strt2);
			l = sprintf(out," FQ_CODEL target %s interval %s"
				" quantum %jd limit %jd flows %jd",
				strt1, strt2,
				(intmax_t) ep->par[3],
				(intmax_t) ep->par[4],
				(intmax_t) ep->par[5]
				);
			if (ep->par[2] & CODEL_ECN_ENABLED)
				l += sprintf(out + l, " ECN");
			else
				l += sprintf(out + l, " NoECN");
			l += sprintf(out + l, "\n");
		} else 	if (!strcasecmp(ep->name,"FQ_PIE")) {
			us_to_time(ep->par[0], strt1);
			us_to_time(ep->par[1], strt2);
			us_to_time(ep->par[2], strt3);
			l = sprintf(out, "  FQ_PIE target %s tupdate %s alpha "
				"%g beta %g max_burst %s max_ecnth %.3g"
				" quantum %jd limit %jd flows %jd",
				strt1,
				strt2,
				ep->par[4] / (float) PIE_SCALE,
				ep->par[5] / (float) PIE_SCALE,
				strt3,
				ep->par[3] / (float) PIE_SCALE,
				(intmax_t) ep->par[7],
				(intmax_t) ep->par[8],
				(intmax_t) ep->par[9]
			);
			
			if (ep->par[6] & PIE_ECN_ENABLED)
				l += sprintf(out + l, " ECN");
			else
				l += sprintf(out + l, " NoECN");
			if (ep->par[6] & PIE_CAPDROP_ENABLED)
				l += sprintf(out + l, " CapDrop");
			else
				l += sprintf(out + l, " NoCapDrop");
			if (ep->par[6] & PIE_ON_OFF_MODE_ENABLED)
				l += sprintf(out + l, " OnOff");
			if (ep->par[6] & PIE_DEPRATEEST_ENABLED)
				l += sprintf(out + l, " DRE");
			else
				l += sprintf(out + l, " TS");
			if (ep->par[6] & PIE_DERAND_ENABLED)
				l += sprintf(out + l, " Derand");
			else
				l += sprintf(out + l, " NoDerand");
			l += sprintf(out + l, "\n");
		}
		break;
	}

	free(ep);
}