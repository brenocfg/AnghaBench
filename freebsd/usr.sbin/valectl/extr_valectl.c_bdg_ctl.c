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
struct nmreq {char* nr_name; int nr_cmd; int nr_arg2; int nr_arg1; int nr_tx_rings; char* nr_rx_rings; int /*<<< orphan*/  nr_flags; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_ringid; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_version; } ;
typedef  int /*<<< orphan*/  nmr ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,...) ; 
 int /*<<< orphan*/  ND (char*,char const*,...) ; 
 int /*<<< orphan*/  NETMAP_API ; 
#define  NETMAP_BDG_ATTACH 134 
#define  NETMAP_BDG_DELIF 133 
#define  NETMAP_BDG_DETACH 132 
 int NETMAP_BDG_HOST ; 
#define  NETMAP_BDG_LIST 131 
#define  NETMAP_BDG_NEWIF 130 
#define  NETMAP_BDG_POLLING_OFF 129 
#define  NETMAP_BDG_POLLING_ON 128 
 int /*<<< orphan*/  NIOCGINFO ; 
 int /*<<< orphan*/  NIOCREGIF ; 
 int /*<<< orphan*/  NR_REG_ALL_NIC ; 
 int /*<<< orphan*/  NR_REG_NIC_SW ; 
 int /*<<< orphan*/  NR_REG_ONE_NIC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  bzero (struct nmreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct nmreq*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_nmr_config (char*,struct nmreq*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int
bdg_ctl(const char *name, int nr_cmd, int nr_arg, char *nmr_config, int nr_arg2)
{
	struct nmreq nmr;
	int error = 0;
	int fd = open("/dev/netmap", O_RDWR);

	if (fd == -1) {
		D("Unable to open /dev/netmap");
		return -1;
	}

	bzero(&nmr, sizeof(nmr));
	nmr.nr_version = NETMAP_API;
	if (name != NULL) /* might be NULL */
		strncpy(nmr.nr_name, name, sizeof(nmr.nr_name)-1);
	nmr.nr_cmd = nr_cmd;
	parse_nmr_config(nmr_config, &nmr);
	nmr.nr_arg2 = nr_arg2;

	switch (nr_cmd) {
	case NETMAP_BDG_DELIF:
	case NETMAP_BDG_NEWIF:
		error = ioctl(fd, NIOCREGIF, &nmr);
		if (error == -1) {
			ND("Unable to %s %s", nr_cmd == NETMAP_BDG_DELIF ? "delete":"create", name);
			perror(name);
		} else {
			ND("Success to %s %s", nr_cmd == NETMAP_BDG_DELIF ? "delete":"create", name);
		}
		break;
	case NETMAP_BDG_ATTACH:
	case NETMAP_BDG_DETACH:
		nmr.nr_flags = NR_REG_ALL_NIC;
		if (nr_arg && nr_arg != NETMAP_BDG_HOST) {
			nmr.nr_flags = NR_REG_NIC_SW;
			nr_arg = 0;
		}
		nmr.nr_arg1 = nr_arg;
		error = ioctl(fd, NIOCREGIF, &nmr);
		if (error == -1) {
			ND("Unable to %s %s to the bridge", nr_cmd ==
			    NETMAP_BDG_DETACH?"detach":"attach", name);
			perror(name);
		} else
			ND("Success to %s %s to the bridge", nr_cmd ==
			    NETMAP_BDG_DETACH?"detach":"attach", name);
		break;

	case NETMAP_BDG_LIST:
		if (strlen(nmr.nr_name)) { /* name to bridge/port info */
			error = ioctl(fd, NIOCGINFO, &nmr);
			if (error) {
				ND("Unable to obtain info for %s", name);
				perror(name);
			} else
				D("%s at bridge:%d port:%d", name, nmr.nr_arg1,
				    nmr.nr_arg2);
			break;
		}

		/* scan all the bridges and ports */
		nmr.nr_arg1 = nmr.nr_arg2 = 0;
		for (; !ioctl(fd, NIOCGINFO, &nmr); nmr.nr_arg2++) {
			D("bridge:%d port:%d %s", nmr.nr_arg1, nmr.nr_arg2,
			    nmr.nr_name);
			nmr.nr_name[0] = '\0';
		}

		break;

	case NETMAP_BDG_POLLING_ON:
	case NETMAP_BDG_POLLING_OFF:
		/* We reuse nmreq fields as follows:
		 *   nr_tx_slots: 0 and non-zero indicate REG_ALL_NIC
		 *                REG_ONE_NIC, respectively.
		 *   nr_rx_slots: CPU core index. This also indicates the
		 *                first queue in the case of REG_ONE_NIC
		 *   nr_tx_rings: (REG_ONE_NIC only) indicates the
		 *                number of CPU cores or the last queue
		 */
		nmr.nr_flags |= nmr.nr_tx_slots ?
			NR_REG_ONE_NIC : NR_REG_ALL_NIC;
		nmr.nr_ringid = nmr.nr_rx_slots;
		/* number of cores/rings */
		if (nmr.nr_flags == NR_REG_ALL_NIC)
			nmr.nr_arg1 = 1;
		else
			nmr.nr_arg1 = nmr.nr_tx_rings;

		error = ioctl(fd, NIOCREGIF, &nmr);
		if (!error)
			D("polling on %s %s", nmr.nr_name,
				nr_cmd == NETMAP_BDG_POLLING_ON ?
				"started" : "stopped");
		else
			D("polling on %s %s (err %d)", nmr.nr_name,
				nr_cmd == NETMAP_BDG_POLLING_ON ?
				"couldn't start" : "couldn't stop", error);
		break;

	default: /* GINFO */
		nmr.nr_cmd = nmr.nr_arg1 = nmr.nr_arg2 = 0;
		error = ioctl(fd, NIOCGINFO, &nmr);
		if (error) {
			ND("Unable to get if info for %s", name);
			perror(name);
		} else
			D("%s: %d queues.", name, nmr.nr_rx_rings);
		break;
	}
	close(fd);
	return error;
}