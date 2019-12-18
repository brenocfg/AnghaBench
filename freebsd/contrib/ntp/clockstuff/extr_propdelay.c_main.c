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
 scalar_t__ Cflag ; 
 int EOF ; 
 scalar_t__ Gflag ; 
 scalar_t__ SUMMERHEIGHT ; 
 scalar_t__ WINTERHEIGHT ; 
 scalar_t__ Wflag ; 
 double atof (char*) ; 
 char* chulat ; 
 char* chulong ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  doit (double,double,double,double,double,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* goes_east_long ; 
 char* goes_sat_lat ; 
 char* goes_stby_long ; 
 char* goes_up_lat ; 
 char* goes_up_long ; 
 char* goes_west_long ; 
 double height ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  init_lib () ; 
 double latlong (char*,int) ; 
 int ntp_getopt (int,char**,char*) ; 
 char* ntp_optarg ; 
 int ntp_optind ; 
 char* progname ; 
 int /*<<< orphan*/  satdoit (double,double,double,double,double,double,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* wwvhlat ; 
 char* wwvhlong ; 
 char* wwvlat ; 
 char* wwvlong ; 

int
main(
	int argc,
	char *argv[]
	)
{
	int c;
	int errflg = 0;
	double lat1, long1;
	double lat2, long2;
	double lat3, long3;

	init_lib();

	progname = argv[0];
	while ((c = ntp_getopt(argc, argv, "dh:CWG")) != EOF)
	    switch (c) {
		case 'd':
		    ++debug;
		    break;
		case 'h':
		    hflag++;
		    height = atof(ntp_optarg);
		    if (height <= 0.0) {
			    (void) fprintf(stderr, "height %s unlikely\n",
					   ntp_optarg);
			    errflg++;
		    }
		    break;
		case 'C':
		    Cflag++;
		    break;
		case 'W':
		    Wflag++;
		    break;
		case 'G':
		    Gflag++;
		    break;
		default:
		    errflg++;
		    break;
	    }
	if (errflg || (!(Cflag || Wflag || Gflag) && ntp_optind+4 != argc) || 
	    ((Cflag || Wflag || Gflag) && ntp_optind+2 != argc)) {
		(void) fprintf(stderr,
			       "usage: %s [-d] [-h height] lat1 long1 lat2 long2\n",
			       progname);
		(void) fprintf(stderr," - or -\n");
		(void) fprintf(stderr,
			       "usage: %s -CWG [-d] lat long\n",
			       progname);
		exit(2);
	}

		   
	if (!(Cflag || Wflag || Gflag)) {
		lat1 = latlong(argv[ntp_optind], 1);
		long1 = latlong(argv[ntp_optind + 1], 0);
		lat2 = latlong(argv[ntp_optind + 2], 1);
		long2 = latlong(argv[ntp_optind + 3], 0);
		if (hflag) {
			doit(lat1, long1, lat2, long2, height, "");
		} else {
			doit(lat1, long1, lat2, long2, (double)SUMMERHEIGHT,
			     "summer propagation, ");
			doit(lat1, long1, lat2, long2, (double)WINTERHEIGHT,
			     "winter propagation, ");
		}
	} else if (Wflag) {
		/*
		 * Compute delay from WWV
		 */
		lat1 = latlong(argv[ntp_optind], 1);
		long1 = latlong(argv[ntp_optind + 1], 0);
		lat2 = latlong(wwvlat, 1);
		long2 = latlong(wwvlong, 0);
		if (hflag) {
			doit(lat1, long1, lat2, long2, height, "WWV  ");
		} else {
			doit(lat1, long1, lat2, long2, (double)SUMMERHEIGHT,
			     "WWV  summer propagation, ");
			doit(lat1, long1, lat2, long2, (double)WINTERHEIGHT,
			     "WWV  winter propagation, ");
		}

		/*
		 * Compute delay from WWVH
		 */
		lat2 = latlong(wwvhlat, 1);
		long2 = latlong(wwvhlong, 0);
		if (hflag) {
			doit(lat1, long1, lat2, long2, height, "WWVH ");
		} else {
			doit(lat1, long1, lat2, long2, (double)SUMMERHEIGHT,
			     "WWVH summer propagation, ");
			doit(lat1, long1, lat2, long2, (double)WINTERHEIGHT,
			     "WWVH winter propagation, ");
		}
	} else if (Cflag) {
		lat1 = latlong(argv[ntp_optind], 1);
		long1 = latlong(argv[ntp_optind + 1], 0);
		lat2 = latlong(chulat, 1);
		long2 = latlong(chulong, 0);
		if (hflag) {
			doit(lat1, long1, lat2, long2, height, "CHU ");
		} else {
			doit(lat1, long1, lat2, long2, (double)SUMMERHEIGHT,
			     "CHU summer propagation, ");
			doit(lat1, long1, lat2, long2, (double)WINTERHEIGHT,
			     "CHU winter propagation, ");
		}
	} else if (Gflag) {
		lat1 = latlong(goes_up_lat, 1);
		long1 = latlong(goes_up_long, 0);
		lat3 = latlong(argv[ntp_optind], 1);
		long3 = latlong(argv[ntp_optind + 1], 0);

		lat2 = latlong(goes_sat_lat, 1);

		long2 = latlong(goes_west_long, 0);
		satdoit(lat1, long1, lat2, long2, lat3, long3,
			"GOES Delay via WEST");

		long2 = latlong(goes_stby_long, 0);
		satdoit(lat1, long1, lat2, long2, lat3, long3,
			"GOES Delay via STBY");

		long2 = latlong(goes_east_long, 0);
		satdoit(lat1, long1, lat2, long2, lat3, long3,
			"GOES Delay via EAST");

	}
	exit(0);
}