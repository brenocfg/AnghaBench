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

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*,...) ; 
 int /*<<< orphan*/  IB_DEST_DRPATH ; 
 int /*<<< orphan*/  IB_DEST_GUID ; 
 int /*<<< orphan*/  IB_DEST_LID ; 
 long INT_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* get_build_version () ; 
 char* getpass (char*) ; 
 char* ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 int /*<<< orphan*/  ibd_dest_type ; 
 int /*<<< orphan*/  ibd_mkey ; 
 int /*<<< orphan*/ * ibd_sm_id ; 
 int ibd_timeout ; 
 int /*<<< orphan*/  ibdebug ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 int /*<<< orphan*/  ibverbose ; 
 int /*<<< orphan*/  madrpc_set_timeout (int) ; 
 int /*<<< orphan*/  madrpc_show_errors (int) ; 
 char* prog_name ; 
 int /*<<< orphan*/  read_ibdiag_config (char*) ; 
 int /*<<< orphan*/  resolve_portid_str (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int show_keys ; 
 int /*<<< orphan*/  sm_portid ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umad_debug (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_opt(int ch, char *optarg)
{
	char *endp;
	long val;

	switch (ch) {
	case 'z':
		read_ibdiag_config(optarg);
		break;
	case 'h':
		ibdiag_show_usage();
		break;
	case 'V':
		fprintf(stderr, "%s %s\n", prog_name, get_build_version());
		exit(0);
	case 'e':
		madrpc_show_errors(1);
		break;
	case 'v':
		ibverbose++;
		break;
	case 'd':
		ibdebug++;
		madrpc_show_errors(1);
		umad_debug(ibdebug - 1);
		break;
	case 'C':
		ibd_ca = optarg;
		break;
	case 'P':
		ibd_ca_port = strtoul(optarg, 0, 0);
		if (ibd_ca_port < 0)
			IBEXIT("cannot resolve CA port %d", ibd_ca_port);
		break;
	case 'D':
		ibd_dest_type = IB_DEST_DRPATH;
		break;
	case 'L':
		ibd_dest_type = IB_DEST_LID;
		break;
	case 'G':
		ibd_dest_type = IB_DEST_GUID;
		break;
	case 't':
		errno = 0;
		val = strtol(optarg, &endp, 0);
		if (errno || (endp && *endp != '\0') || val <= 0 ||
		    val > INT_MAX)
			IBEXIT("Invalid timeout \"%s\".  Timeout requires a "
				"positive integer value < %d.", optarg, INT_MAX);
		else {
			madrpc_set_timeout((int)val);
			ibd_timeout = (int)val;
		}
		break;
	case 's':
		/* srcport is not required when resolving via IB_DEST_LID */
		if (resolve_portid_str(ibd_ca, ibd_ca_port, &sm_portid, optarg,
				IB_DEST_LID, 0, NULL) < 0)
			IBEXIT("cannot resolve SM destination port %s",
				optarg);
		ibd_sm_id = &sm_portid;
		break;
	case 'K':
		show_keys = 1;
		break;
	case 'y':
		errno = 0;
		ibd_mkey = strtoull(optarg, &endp, 0);
		if (errno || *endp != '\0') {
			errno = 0;
			ibd_mkey = strtoull(getpass("M_Key: "), &endp, 0);
			if (errno || *endp != '\0') {
				IBEXIT("Bad M_Key");
			}
                }
                break;
	default:
		return -1;
	}

	return 0;
}