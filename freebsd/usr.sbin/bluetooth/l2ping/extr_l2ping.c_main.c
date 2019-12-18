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
typedef  char uint8_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_l2cap {int l2cap_len; char l2cap_bdaddr; void* l2cap_family; } ;
struct sockaddr {int dummy; } ;
struct ng_btsocket_l2cap_raw_ping {int result; int echo_size; char* echo_data; } ;
struct hostent {char* h_addr; char* h_name; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  ng_l2cap_cmd_hdr_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dst ;
typedef  char bdaddr_t ;

/* Variables and functions */
 void* AF_BLUETOOTH ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_L2CAP ; 
 char* NG_HCI_BDADDR_ANY ; 
 int NG_L2CAP_MAX_ECHO_SIZE ; 
 int NG_L2CAP_MTU_MINIMUM ; 
 int /*<<< orphan*/  PATTERN_SIZE ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SIOC_L2CAP_L2CA_PING ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bt_aton (int /*<<< orphan*/ ,char*) ; 
 struct hostent* bt_gethostbyaddr (char const*,int,void*) ; 
 struct hostent* bt_gethostbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ntoa (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_l2cap_raw_ping*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_l2cap*,int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  optarg ; 
 char* pattern ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (char*) ; 
 char* strerror (int) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 double tv2msec (struct timeval*) ; 
 int /*<<< orphan*/  tv_sub (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	bdaddr_t		 src, dst;
	struct hostent		*he;
	uint8_t			*echo_data;
	struct sockaddr_l2cap	 sa;
	int32_t			 n, s, count, wait, flood, echo_size, numeric;
	char			*endp, *rname;

	/* Set defaults */
	memcpy(&src, NG_HCI_BDADDR_ANY, sizeof(src));
	memcpy(&dst, NG_HCI_BDADDR_ANY, sizeof(dst));

	echo_data = (uint8_t *) calloc(NG_L2CAP_MAX_ECHO_SIZE, sizeof(uint8_t));
	if (echo_data == NULL) {
		fprintf(stderr, "Failed to allocate echo data buffer");
		exit(1);
	}

	/*
	 * Set default echo size to the NG_L2CAP_MTU_MINIMUM minus
	 * the size of the L2CAP signalling command header.
	 */

	echo_size = NG_L2CAP_MTU_MINIMUM - sizeof(ng_l2cap_cmd_hdr_t);
	count = -1; /* unimited */
	wait = 1;   /* sec */
	flood = 0;
	numeric = 0;

	/* Parse command line arguments */
	while ((n = getopt(argc, argv, "a:c:fi:nS:s:h")) != -1) {
		switch (n) {
		case 'a':
			if (!bt_aton(optarg, &dst)) {
				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(1, "%s: %s", optarg, hstrerror(h_errno));

				memcpy(&dst, he->h_addr, sizeof(dst));
			}
			break;

		case 'c':
			count = strtol(optarg, &endp, 10);
			if (count <= 0 || *endp != '\0')
				usage();
			break;

		case 'f':
			flood = 1;
			break;

		case 'i':
			wait = strtol(optarg, &endp, 10);
			if (wait <= 0 || *endp != '\0')
				usage();
			break;

		case 'n':
			numeric = 1;
			break;

		case 'S':
			if (!bt_aton(optarg, &src)) {
				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(1, "%s: %s", optarg, hstrerror(h_errno));

				memcpy(&src, he->h_addr, sizeof(src));
			}
			break;

		case 's':
                        echo_size = strtol(optarg, &endp, 10);
                        if (echo_size < sizeof(int32_t) ||
			    echo_size > NG_L2CAP_MAX_ECHO_SIZE ||
			    *endp != '\0')
				usage();
			break;

		case 'h':
		default:
			usage();
			break;
		}
	}

	if (memcmp(&dst, NG_HCI_BDADDR_ANY, sizeof(dst)) == 0)
		usage();

	he = bt_gethostbyaddr((const char *)&dst, sizeof(dst), AF_BLUETOOTH);
	if (he == NULL || he->h_name == NULL || he->h_name[0] == '\0' || numeric)
		asprintf(&rname, "%s", bt_ntoa(&dst, NULL));
	else
		rname = strdup(he->h_name);

	if (rname == NULL)
		errx(1, "Failed to create remote hostname");

	s = socket(PF_BLUETOOTH, SOCK_RAW, BLUETOOTH_PROTO_L2CAP);
	if (s < 0)
		err(2, "Could not create socket");

	memset(&sa, 0, sizeof(sa));
	sa.l2cap_len = sizeof(sa);
	sa.l2cap_family = AF_BLUETOOTH;
	memcpy(&sa.l2cap_bdaddr, &src, sizeof(sa.l2cap_bdaddr));

	if (bind(s, (struct sockaddr *) &sa, sizeof(sa)) < 0)
		err(3,
"Could not bind socket, src bdaddr=%s", bt_ntoa(&sa.l2cap_bdaddr, NULL));

	memset(&sa, 0, sizeof(sa));
	sa.l2cap_len = sizeof(sa);
	sa.l2cap_family = AF_BLUETOOTH;
	memcpy(&sa.l2cap_bdaddr, &dst, sizeof(sa.l2cap_bdaddr));

	if (connect(s, (struct sockaddr *) &sa, sizeof(sa)) < 0)
		err(4,
"Could not connect socket, dst bdaddr=%s", bt_ntoa(&sa.l2cap_bdaddr, NULL));

	/* Fill pattern */
	for (n = 0; n < echo_size; ) {
		int32_t	avail = min(echo_size - n, PATTERN_SIZE);

		memcpy(echo_data + n, pattern, avail);
		n += avail;
	}

	/* Start ping'ing */
	for (n = 0; count == -1 || count > 0; n ++) {
		struct ng_btsocket_l2cap_raw_ping	r;
		struct timeval				a, b;
		int32_t					fail;

		if (gettimeofday(&a, NULL) < 0)
			err(5, "Could not gettimeofday(a)");

		fail = 0;
		*((int32_t *) echo_data) = htonl(n);

		r.result = 0;
		r.echo_size = echo_size;
		r.echo_data = echo_data;
		if (ioctl(s, SIOC_L2CAP_L2CA_PING, &r, sizeof(r)) < 0) {
			r.result = errno;
			fail = 1;
/*
			warn("Could not ping, dst bdaddr=%s",
				bt_ntoa(&r.echo_dst, NULL));
*/
		}

		if (gettimeofday(&b, NULL) < 0)
			err(7, "Could not gettimeofday(b)");

		tv_sub(&b, &a);

		fprintf(stdout,
"%d bytes from %s seq_no=%d time=%.3f ms result=%#x %s\n",
			r.echo_size,
			rname,
			ntohl(*((int32_t *)(r.echo_data))),
			tv2msec(&b), r.result,
			((fail == 0)? "" : strerror(errno)));

		if (!flood) {
			/* Wait */
			a.tv_sec = wait;
			a.tv_usec = 0;
			select(0, NULL, NULL, NULL, &a);
		}

		if (count != -1)
			count --;
	}

	free(rname);
	free(echo_data);
	close(s);

	return (0);
}