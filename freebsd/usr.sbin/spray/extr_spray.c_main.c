#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int u_int ;
struct TYPE_6__ {double sec; double usec; } ;
struct TYPE_7__ {int counter; TYPE_1__ clock; } ;
typedef  TYPE_2__ spraycumul ;
struct TYPE_8__ {int sprayarr_len; int /*<<< orphan*/  sprayarr_val; } ;
typedef  TYPE_3__ sprayarr ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSET_TIMEOUT ; 
 int /*<<< orphan*/  NO_DEFAULT ; 
 int /*<<< orphan*/  ONE_WAY ; 
 scalar_t__ RPC_SUCCESS ; 
 int SPRAYMAX ; 
 int SPRAYOVERHEAD ; 
 int /*<<< orphan*/  SPRAYPROC_CLEAR ; 
 int /*<<< orphan*/  SPRAYPROC_GET ; 
 int /*<<< orphan*/  SPRAYPROC_SPRAY ; 
 int /*<<< orphan*/  SPRAYPROG ; 
 int /*<<< orphan*/  SPRAYVERS ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_xferstats (int,int,double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spray_buffer ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ xdr_sprayarr ; 
 scalar_t__ xdr_spraycumul ; 
 scalar_t__ xdr_void ; 

int
main(int argc, char *argv[])
{
	spraycumul	host_stats;
	sprayarr	host_array;
	CLIENT *cl;
	int c;
	u_int i;
	u_int count = 0;
	int delay = 0;
	int length = 0;
	double xmit_time;			/* time to receive data */

	while ((c = getopt(argc, argv, "c:d:l:")) != -1) {
		switch (c) {
		case 'c':
			count = atoi(optarg);
			break;
		case 'd':
			delay = atoi(optarg);
			break;
		case 'l':
			length = atoi(optarg);
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		usage();
		/* NOTREACHED */
	}


	/* Correct packet length. */
	if (length > SPRAYMAX) {
		length = SPRAYMAX;
	} else if (length < SPRAYOVERHEAD) {
		length = SPRAYOVERHEAD;
	} else {
		/* The RPC portion of the packet is a multiple of 32 bits. */
		length -= SPRAYOVERHEAD - 3;
		length &= ~3;
		length += SPRAYOVERHEAD;
	}


	/*
	 * The default value of count is the number of packets required
	 * to make the total stream size 100000 bytes.
	 */
	if (!count) {
		count = 100000 / length;
	}

	/* Initialize spray argument */
	host_array.sprayarr_len = length - SPRAYOVERHEAD;
	host_array.sprayarr_val = spray_buffer;
	

	/* create connection with server */
	cl = clnt_create(*argv, SPRAYPROG, SPRAYVERS, "udp");
	if (cl == NULL)
		errx(1, "%s", clnt_spcreateerror(""));


	/*
	 * For some strange reason, RPC 4.0 sets the default timeout, 
	 * thus timeouts specified in clnt_call() are always ignored.  
	 *
	 * The following (undocumented) hack resets the internal state
	 * of the client handle.
	 */
	clnt_control(cl, CLSET_TIMEOUT, &NO_DEFAULT);


	/* Clear server statistics */
	if (clnt_call(cl, SPRAYPROC_CLEAR, (xdrproc_t)xdr_void, NULL,
		(xdrproc_t)xdr_void, NULL, TIMEOUT) != RPC_SUCCESS)
		errx(1, "%s", clnt_sperror(cl, ""));


	/* Spray server with packets */
	printf ("sending %u packets of length %d to %s ...", count, length,
	    *argv);
	fflush (stdout);

	for (i = 0; i < count; i++) {
		clnt_call(cl, SPRAYPROC_SPRAY, (xdrproc_t)xdr_sprayarr,
		    &host_array, (xdrproc_t)xdr_void, NULL, ONE_WAY);

		if (delay) {
			usleep(delay);
		}
	}


	/* Collect statistics from server */
	if (clnt_call(cl, SPRAYPROC_GET, (xdrproc_t)xdr_void, NULL,
		(xdrproc_t)xdr_spraycumul, &host_stats, TIMEOUT) != RPC_SUCCESS)
		errx(1, "%s", clnt_sperror(cl, ""));

	xmit_time = host_stats.clock.sec +
			(host_stats.clock.usec / 1000000.0);

	printf ("\n\tin %.2f seconds elapsed time\n", xmit_time);


	/* report dropped packets */
	if (host_stats.counter != count) {
		int packets_dropped = count - host_stats.counter;

		printf("\t%d packets (%.2f%%) dropped\n",
			packets_dropped,
			100.0 * packets_dropped / count );
	} else {
		printf("\tno packets dropped\n");
	}

	printf("Sent:");
	print_xferstats(count, length, xmit_time);

	printf("Rcvd:");
	print_xferstats(host_stats.counter, length, xmit_time);
	
	exit (0);
}