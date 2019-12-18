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
typedef  int /*<<< orphan*/  t ;
struct ioat_test {int raw_is_virtual; int verify; int raw_write; int zero_stats; int buffer_size; int chain_depth; int duration; int channel_index; void* transactions; int /*<<< orphan*/  testkind; void* coalesce_period; } ;

/* Variables and functions */
 int EX_OK ; 
 int EX_UNAVAILABLE ; 
 int EX_USAGE ; 
 int /*<<< orphan*/  IOAT_DMATEST ; 
 int /*<<< orphan*/  IOAT_TEST_DMA ; 
 int /*<<< orphan*/  IOAT_TEST_DMA_8K ; 
 int /*<<< orphan*/  IOAT_TEST_DMA_CRC ; 
 int /*<<< orphan*/  IOAT_TEST_DMA_CRC_COPY ; 
 int /*<<< orphan*/  IOAT_TEST_FILL ; 
 int /*<<< orphan*/  IOAT_TEST_MEMCPY ; 
 int /*<<< orphan*/  O_RDWR ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,struct ioat_test*) ; 
 int /*<<< orphan*/  main_raw (struct ioat_test*,int,char**) ; 
 int /*<<< orphan*/  memset (struct ioat_test*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int prettyprint (struct ioat_test*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	struct ioat_test t;
	int fd, ch;
	bool fflag, rflag, Eflag, eflag, mflag, xflag, Xflag;
	unsigned modeflags;

	memset(&t, 0, sizeof(t));

	fflag = rflag = Eflag = eflag = mflag = xflag = Xflag = false;
	modeflags = 0;

	while ((ch = getopt(argc, argv, "c:EefmrvVwxXz")) != -1) {
		switch (ch) {
		case 'c':
			t.coalesce_period = atoi(optarg);
			break;
		case 'E':
			Eflag = true;
			modeflags++;
			break;
		case 'e':
			eflag = true;
			modeflags++;
			break;
		case 'f':
			fflag = true;
			modeflags++;
			break;
		case 'm':
			mflag = true;
			modeflags++;
			break;
		case 'r':
			rflag = true;
			modeflags++;
			break;
		case 'v':
			t.raw_is_virtual = true;
			break;
		case 'V':
			t.verify = true;
			break;
		case 'w':
			t.raw_write = true;
			break;
		case 'x':
			xflag = true;
			modeflags++;
			break;
		case 'X':
			Xflag = true;
			modeflags++;
			break;
		case 'z':
			t.zero_stats = true;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 2)
		usage();

	if (modeflags > 1) {
		printf("Invalid: Cannot use >1 mode flag (-E, -e, -f, -m, -r, -x or -X)\n");
		usage();
	}

	/* Defaults for optional args */
	t.buffer_size = 256 * 1024;
	t.chain_depth = 2;
	t.duration = 0;
	t.testkind = IOAT_TEST_DMA;

	if (fflag)
		t.testkind = IOAT_TEST_FILL;
	else if (Eflag || eflag) {
		t.testkind = IOAT_TEST_DMA_8K;
		t.buffer_size = 8 * 1024;
	} else if (mflag)
		t.testkind = IOAT_TEST_MEMCPY;
	else if (xflag)
		t.testkind = IOAT_TEST_DMA_CRC;
	else if (Xflag)
		t.testkind = IOAT_TEST_DMA_CRC_COPY;

	t.channel_index = atoi(argv[0]);
	if (t.channel_index > 8) {
		printf("Channel number must be between 0 and 7.\n");
		return (EX_USAGE);
	}

	if (rflag) {
		main_raw(&t, argc, argv);
		return (EX_OK);
	}

	t.transactions = atoi(argv[1]);

	if (argc >= 3) {
		t.buffer_size = atoi(argv[2]);
		if (t.buffer_size == 0) {
			printf("Buffer size must be greater than zero\n");
			return (EX_USAGE);
		}
	}

	if (argc >= 4) {
		t.chain_depth = atoi(argv[3]);
		if (t.chain_depth < 1) {
			printf("Chain length must be greater than zero\n");
			return (EX_USAGE);
		}
	}

	if (argc >= 5) {
		t.duration = atoi(argv[4]);
		if (t.duration < 1) {
			printf("Duration must be greater than zero\n");
			return (EX_USAGE);
		}
	}

	fd = open("/dev/ioat_test", O_RDWR);
	if (fd < 0) {
		printf("Cannot open /dev/ioat_test\n");
		return (EX_UNAVAILABLE);
	}

	(void)ioctl(fd, IOAT_DMATEST, &t);
	close(fd);

	return (prettyprint(&t));
}