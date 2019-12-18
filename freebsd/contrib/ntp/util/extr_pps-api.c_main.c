#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_5__ {int mode; } ;
typedef  TYPE_1__ pps_params_t ;
struct TYPE_6__ {scalar_t__ assert_sequence; scalar_t__ clear_sequence; int /*<<< orphan*/  clear_timestamp; int /*<<< orphan*/  assert_timestamp; } ;
typedef  TYPE_2__ pps_info_t ;
typedef  int /*<<< orphan*/  pps_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  Chew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PPS_CAPTUREASSERT ; 
 int PPS_CAPTUREBOTH ; 
 int PPS_ECHOASSERT ; 
 int /*<<< orphan*/  PPS_TSFMT_TSPEC ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int time_pps_create (int,int /*<<< orphan*/ *) ; 
 int time_pps_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,struct timespec*) ; 
 int time_pps_getcap (int /*<<< orphan*/ ,int*) ; 
 int time_pps_setparams (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usleep (int) ; 

int
main(int argc, char **argv)
{
	int fd;
	pps_info_t pi;
	pps_params_t pp;
	pps_handle_t ph;
	int i, mode;
	u_int olda, oldc;
	double d = 0;
	struct timespec to;

	if (argc < 2)
		argv[1] = "/dev/cuaa1";
	setbuf(stdout, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) 
		err(1, argv[1]);
	i = time_pps_create(fd, &ph);
	if (i < 0)
		err(1, "time_pps_create");

	i = time_pps_getcap(ph, &mode);
	if (i < 0)
		err(1, "time_pps_getcap");

	pp.mode = PPS_CAPTUREASSERT | PPS_ECHOASSERT;
	pp.mode = PPS_CAPTUREBOTH;
	/* pp.mode = PPS_CAPTUREASSERT; */

	i = time_pps_setparams(ph, &pp);
	if (i < 0)
		err(1, "time_pps_setparams");

	while (1) {
		to.tv_nsec = 0;
		to.tv_sec = 0;
		i = time_pps_fetch(ph, PPS_TSFMT_TSPEC, &pi, &to);
		if (i < 0)
			err(1, "time_pps_fetch");
		if (olda == pi.assert_sequence &&
		    oldc == pi.clear_sequence) {
			usleep(10000);
			continue;
		}

		Chew(&pi.assert_timestamp, &pi.clear_timestamp,
			pi.assert_sequence, pi.clear_sequence);
		olda = pi.assert_sequence;
		oldc = pi.clear_sequence;
	}

	return(0);
}