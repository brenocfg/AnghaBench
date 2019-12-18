#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_min; int tm_hour; int tm_yday; int tm_year; int tm_sec; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  device ;
typedef  int /*<<< orphan*/  code ;
struct TYPE_7__ {int port; int gain; int sample_rate; int channels; int precision; int encoding; } ;
struct TYPE_8__ {TYPE_1__ play; } ;
typedef  TYPE_2__ audio_info_t ;
struct TYPE_11__ {int sw; int arg; } ;
struct TYPE_10__ {int sw; int arg; } ;
struct TYPE_9__ {int sw; int arg; } ;

/* Variables and functions */
 int AUDIO_ENCODING_ULAW ; 
 int /*<<< orphan*/  AUDIO_GETINFO ; 
 int /*<<< orphan*/  AUDIO_SETINFO ; 
 int AUDIO_SPEAKER ; 
#define  COEF 137 
#define  DATA 136 
 int DATA0 ; 
 int DATA1 ; 
#define  DEC 135 
 int /*<<< orphan*/  DEVICE ; 
#define  DST1 134 
#define  DST2 133 
#define  DUT1 132 
 int /*<<< orphan*/  HIGH ; 
#define  IRIG 131 
#define  LEAP 130 
 int /*<<< orphan*/  LOW ; 
 int M2 ; 
 int M5 ; 
 int M8 ; 
#define  MIN 129 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int SECOND ; 
#define  WWV 128 
 int abs (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  dst ; 
 int dut1 ; 
 int encode ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fd ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ leap ; 
 int level ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  peep (int,int,int /*<<< orphan*/ ) ; 
 int port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_5__* progx ; 
 TYPE_4__* progy ; 
 TYPE_3__* progz ; 
 int /*<<< orphan*/  sec (int) ; 
 int second ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,...) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int tone ; 
 int /*<<< orphan*/  utc ; 

int
main(
	int	argc,		/* command line options */
	char	**argv		/* poiniter to list of tokens */
	)
{
	struct timeval tv;	/* system clock at startup */
	audio_info_t info;	/* Sun audio structure */
	struct tm *tm = NULL;	/* structure returned by gmtime */
	char	device[50];	/* audio device */
	char	code[100];	/* timecode */
	int	rval, temp, arg, sw, ptr;
	int	minute, hour, day, year;
	int	i;

	/*
	 * Parse options
	 */
	strlcpy(device, DEVICE, sizeof(device));
	year = 0;
	while ((temp = getopt(argc, argv, "a:dhilsu:v:y:")) != -1) {
		switch (temp) {

		case 'a':	/* specify audio device (/dev/audio) */
			strlcpy(device, optarg, sizeof(device));
			break;

		case 'd':	/* set DST for summer (WWV/H only) */
			dst++;
			break;

		case 'h':	/* select WWVH sync frequency */
			tone = 1200;
			break;

		case 'i':	/* select irig format */
			encode = IRIG;
			break;

		case 'l':	/* set leap warning bit (WWV/H only) */
			leap++;
			break;

		case 's':	/* enable speaker */
			port |= AUDIO_SPEAKER;
			break;

		case 'u':	/* set DUT1 offset (-7 to +7) */
			sscanf(optarg, "%d", &dut1);
			if (dut1 < 0)
				dut1 = abs(dut1);
			else
				dut1 |= 0x8;
			break;

		case 'v':	/* set output level (0-255) */
			sscanf(optarg, "%d", &level);
			break;

		case 'y':	/* set initial date and time */
			sscanf(optarg, "%2d%3d%2d%2d", &year, &day,
			    &hour, &minute);
			utc++;
			break;

		defult:
			printf("invalid option %c\n", temp);
			break;
		}
	}

	/*
	 * Open audio device and set options
	 */
	fd = open("/dev/audio", O_WRONLY);
	if (fd <= 0) {
		printf("audio open %s\n", strerror(errno));
		exit(1);
	}
	rval = ioctl(fd, AUDIO_GETINFO, &info);
	if (rval < 0) {
		printf("audio control %s\n", strerror(errno));
		exit(0);
	}
	info.play.port = port;
	info.play.gain = level;
	info.play.sample_rate = SECOND;
	info.play.channels = 1;
	info.play.precision = 8;
	info.play.encoding = AUDIO_ENCODING_ULAW;
	printf("port %d gain %d rate %d chan %d prec %d encode %d\n",
	    info.play.port, info.play.gain, info.play.sample_rate,
	    info.play.channels, info.play.precision,
	    info.play.encoding);
	ioctl(fd, AUDIO_SETINFO, &info);

 	/*
	 * Unless specified otherwise, read the system clock and
	 * initialize the time.
	 */
	if (!utc) {
		gettimeofday(&tv, NULL);
		tm = gmtime(&tv.tv_sec);
		minute = tm->tm_min;
		hour = tm->tm_hour;
		day = tm->tm_yday + 1;
		year = tm->tm_year % 100;
		second = tm->tm_sec;

		/*
		 * Delay the first second so the generator is accurately
		 * aligned with the system clock within one sample (125
		 * microseconds ).
		 */
		delay(SECOND - tv.tv_usec * 8 / 1000);
	}
	memset(code, 0, sizeof(code));
	switch (encode) {

	/*
	 * For WWV/H and default time, carefully set the signal
	 * generator seconds number to agree with the current time.
	 */ 
	case WWV:
		printf("year %d day %d time %02d:%02d:%02d tone %d\n",
		    year, day, hour, minute, second, tone);
		snprintf(code, sizeof(code), "%01d%03d%02d%02d%01d",
		    year / 10, day, hour, minute, year % 10);
		printf("%s\n", code);
		ptr = 8;
		for (i = 0; i <= second; i++) {
			if (progx[i].sw == DEC)
				ptr--;
		}
		break;

	/*
	 * For IRIG the signal generator runs every second, so requires
	 * no additional alignment.
	 */
	case IRIG:
		printf("sbs %x year %d day %d time %02d:%02d:%02d\n",
		    0, year, day, hour, minute, second);
		break;
	}

	/*
	 * Run the signal generator to generate new timecode strings
	 * once per minute for WWV/H and once per second for IRIG.
	 */
	while(1) {

		/*
		 * Crank the state machine to propagate carries to the
		 * year of century. Note that we delayed up to one
		 * second for alignment after reading the time, so this
		 * is the next second.
		 */
		second = (second + 1) % 60;
		if (second == 0) {
			minute++;
			if (minute >= 60) {
				minute = 0;
				hour++;
			}
			if (hour >= 24) {
				hour = 0;
				day++;
			}

			/*
			 * At year rollover check for leap second.
			 */
			if (day >= (year & 0x3 ? 366 : 367)) {
				if (leap) {
					sec(DATA0);
					printf("\nleap!");
					leap = 0;
				}
				day = 1;
				year++;
			}
			if (encode == WWV) {
				snprintf(code, sizeof(code),
				    "%01d%03d%02d%02d%01d", year / 10,
				    day, hour, minute, year % 10);
				printf("\n%s\n", code);
				ptr = 8;
			}
		}
		if (encode == IRIG) {
			snprintf(code, sizeof(code),
			    "%04x%04d%06d%02d%02d%02d", 0, year, day,
			    hour, minute, second);
			printf("%s\n", code);
			ptr = 19;
		}

		/*
		 * Generate data for the second
		 */
		switch(encode) {

		/*
		 * The IRIG second consists of 20 BCD digits of width-
		 * modulateod pulses at 2, 5 and 8 ms and modulated 50
		 * percent on the 1000-Hz carrier.
		 */
		case IRIG:
			for (i = 0; i < 100; i++) {
				if (i < 10) {
					sw = progz[i].sw;
					arg = progz[i].arg;
				} else {
					sw = progy[i % 10].sw;
					arg = progy[i % 10].arg;
				}
				switch(sw) {

				case COEF:	/* send BCD bit */
					if (code[ptr] & arg) {
						peep(M5, 1000, HIGH);
						peep(M5, 1000, LOW);
						printf("1");
					} else {
						peep(M2, 1000, HIGH);
						peep(M8, 1000, LOW);
						printf("0");
					}
					break;

				case DEC:	/* send IM/PI bit */
					ptr--;
					printf(" ");
					peep(arg, 1000, HIGH);
					peep(10 - arg, 1000, LOW);
					break;

				case MIN:	/* send data bit */
					peep(arg, 1000, HIGH);
					peep(10 - arg, 1000, LOW);
					printf("M ");
					break;
				}
				if (ptr < 0)
					break;
			}
			printf("\n");
			break;

		/*
		 * The WWV/H second consists of 9 BCD digits of width-
		 * modulateod pulses 200, 500 and 800 ms at 100-Hz.
		 */
		case WWV:
			sw = progx[second].sw;
			arg = progx[second].arg;
			switch(sw) {

			case DATA:		/* send data bit */
				sec(arg);
				break;

			case COEF:		/* send BCD bit */
				if (code[ptr] & arg) {
					sec(DATA1);
					printf("1");
				} else {
					sec(DATA0);
					printf("0");
				}
				break;

			case LEAP:		/* send leap bit */
				if (leap) {
					sec(DATA1);
					printf("L ");
				} else {
					sec(DATA0);
					printf("  ");
				}
				break;

			case DEC:		/* send data bit */
				ptr--;
				sec(arg);
				printf(" ");
				break;

			case MIN:		/* send minute sync */
				peep(arg, tone, HIGH);
				peep(1000 - arg, tone, OFF);
				break;

			case DUT1:		/* send DUT1 bits */
				if (dut1 & arg)
					sec(DATA1);
				else
					sec(DATA0);
				break;
				
			case DST1:		/* send DST1 bit */
				ptr--;
				if (dst)
					sec(DATA1);
				else
					sec(DATA0);
				printf(" ");
				break;

			case DST2:		/* send DST2 bit */
				if (dst)
					sec(DATA1);
				else
					sec(DATA0);
				break;
			}
		}
	}
}