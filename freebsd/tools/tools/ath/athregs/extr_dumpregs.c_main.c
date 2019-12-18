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
typedef  int u_int32_t ;
typedef  int u_int ;
struct ath_driver_req {int dummy; } ;
struct ath_diag {int ad_id; int ad_out_size; int ad_in_size; int /*<<< orphan*/ * ad_out_data; int /*<<< orphan*/  ad_name; scalar_t__ ad_in_data; } ;
typedef  void* caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  ah_phyRev; int /*<<< orphan*/  ah_macRev; int /*<<< orphan*/  ah_macVersion; int /*<<< orphan*/  ah_devid; } ;
struct TYPE_4__ {int show_addrs; int show_names; int /*<<< orphan*/ * regdata; TYPE_1__ revs; } ;
typedef  int /*<<< orphan*/  HAL_REGRANGE ;

/* Variables and functions */
 char* ATH_DEFAULT ; 
 int ATH_DIAG_DYN ; 
 int ATH_DIAG_IN ; 
 int DUMP_ALL ; 
 int DUMP_BASEBAND ; 
 int DUMP_BASIC ; 
 int DUMP_DCU ; 
 int DUMP_INTERRUPT ; 
 int DUMP_KEYCACHE ; 
 int DUMP_QCU ; 
 int DUMP_XR ; 
 int HAL_DIAG_REGS ; 
 int HAL_DIAG_REVS ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 int /*<<< orphan*/  ath_driver_req_close (struct ath_driver_req*) ; 
 scalar_t__ ath_driver_req_fetch_diag (struct ath_driver_req*,int /*<<< orphan*/ ,struct ath_diag*) ; 
 int /*<<< orphan*/  ath_driver_req_init (struct ath_driver_req*) ; 
 scalar_t__ ath_driver_req_open (struct ath_driver_req*,char const*) ; 
 scalar_t__ ath_hal_anyregs (int) ; 
 int /*<<< orphan*/  ath_hal_dumpbb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_dumpdcu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_dumpint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_dumpkeycache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_dumpqcu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_dumpregs (int /*<<< orphan*/ ,int) ; 
 int ath_hal_setupdiagregs (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ath_hal_setupregs (struct ath_diag*,int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ malloc (int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  putchar (char) ; 
 TYPE_2__ state ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct ath_diag atd;
	const char *ifname;
	u_int32_t *data;
	u_int32_t *dp, *ep;
	int what, c, i;
	struct ath_driver_req req;

	ath_driver_req_init(&req);

	ifname = getenv("ATH");
	if (!ifname)
		ifname = ATH_DEFAULT;

	what = 0;
	state.show_addrs = 0;
	state.show_names = 1;
	while ((c = getopt(argc, argv, "i:aAbdkmNqxz")) != -1)
		switch (c) {
		case 'a':
			what |= DUMP_ALL;
			break;
		case 'A':
			state.show_addrs = 1;
			break;
		case 'b':
			what |= DUMP_BASEBAND;
			break;
		case 'd':
			what |= DUMP_DCU;
			break;
		case 'k':
			what |= DUMP_KEYCACHE;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'm':
			what |= DUMP_BASIC;
			break;
		case 'N':
			state.show_names = 0;
			break;
		case 'q':
			what |= DUMP_QCU;
			break;
		case 'x':
			what |= DUMP_XR;
			break;
		case 'z':
			what |= DUMP_INTERRUPT;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}

	/* Initialise the driver interface */
	if (ath_driver_req_open(&req, ifname) < 0) {
		exit(127);
	}

	/*
	 * Whilst we're doing the ath_diag pieces, we have to set this
	 * ourselves.
	 */
	strncpy(atd.ad_name, ifname, sizeof (atd.ad_name));

	argc -= optind;
	argv += optind;
	if (what == 0)
		what = DUMP_BASIC;

	atd.ad_id = HAL_DIAG_REVS;
	atd.ad_out_data = (caddr_t) &state.revs;
	atd.ad_out_size = sizeof(state.revs);

	if (ath_driver_req_fetch_diag(&req, SIOCGATHDIAG, &atd) < 0)
		err(1, "%s", atd.ad_name);

	if (ath_hal_setupregs(&atd, what) == 0)
		errx(-1, "no registers are known for this part "
		    "(devid 0x%x mac %d.%d phy %d)", state.revs.ah_devid,
		    state.revs.ah_macVersion, state.revs.ah_macRev,
		    state.revs.ah_phyRev);

	atd.ad_out_size = ath_hal_setupdiagregs((HAL_REGRANGE *) atd.ad_in_data,
		atd.ad_in_size / sizeof(HAL_REGRANGE));
	atd.ad_out_data = (caddr_t) malloc(atd.ad_out_size);
	if (atd.ad_out_data == NULL) {
		fprintf(stderr, "Cannot malloc output buffer, size %u\n",
			atd.ad_out_size);
		exit(-1);
	}
	atd.ad_id = HAL_DIAG_REGS | ATH_DIAG_IN | ATH_DIAG_DYN;

	if (ath_driver_req_fetch_diag(&req, SIOCGATHDIAG, &atd) < 0)
		err(1, "%s", atd.ad_name);

	/*
	 * Expand register data into global space that can be
	 * indexed directly by register offset.
	 */
	dp = (u_int32_t *)atd.ad_out_data;
	ep = (u_int32_t *)(atd.ad_out_data + atd.ad_out_size);
	while (dp < ep) {
		u_int r = dp[0];	/* start of range */
		u_int e = dp[1];	/* end of range */
		dp++;
		dp++;
		/* convert offsets to indices */
		r >>= 2; e >>= 2;
		do {
			if (dp >= ep) {
				fprintf(stderr, "Warning, botched return data;"
					"register at offset 0x%x not present\n",
					r << 2);
				break;
			}
			state.regdata[r++] = *dp++;
		} while (r <= e);
	} 

	if (what & DUMP_BASIC)
		ath_hal_dumpregs(stdout, DUMP_BASIC);
	if ((what & DUMP_INTERRUPT) && ath_hal_anyregs(DUMP_INTERRUPT)) {
		if (what & DUMP_BASIC)
			putchar('\n');
		if (state.show_addrs)
			ath_hal_dumpregs(stdout, DUMP_INTERRUPT);
		else
			ath_hal_dumpint(stdout, what);
	}
	if ((what & DUMP_QCU) && ath_hal_anyregs(DUMP_QCU)) {
		if (what & (DUMP_BASIC|DUMP_INTERRUPT))
			putchar('\n');
		if (state.show_addrs)
			ath_hal_dumpregs(stdout, DUMP_QCU);
		else
			ath_hal_dumpqcu(stdout, what);
	}
	if ((what & DUMP_DCU) && ath_hal_anyregs(DUMP_DCU)) {
		if (what & (DUMP_BASIC|DUMP_INTERRUPT|DUMP_QCU))
			putchar('\n');
		if (state.show_addrs)
			ath_hal_dumpregs(stdout, DUMP_DCU);
		else
			ath_hal_dumpdcu(stdout, what);
	}
	if (what & DUMP_KEYCACHE) {
		if (state.show_addrs) {
			if (what & (DUMP_BASIC|DUMP_INTERRUPT|DUMP_QCU|DUMP_DCU))
				putchar('\n');
			ath_hal_dumpregs(stdout, DUMP_KEYCACHE);
		} else
			ath_hal_dumpkeycache(stdout, 128);
	}
	if (what & DUMP_BASEBAND) {
		if (what &~ DUMP_BASEBAND)
			fprintf(stdout, "\n");
		ath_hal_dumpbb(stdout, what);
	}
	ath_driver_req_close(&req);
	return 0;
}