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
struct pwm_state {int period; int duty; int enable; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  O_RDWR ; 
 unsigned long const PWMGETSTATE ; 
 unsigned long const PWMSETSTATE ; 
 int PWM_DISABLE ; 
 int PWM_DUTY ; 
 int PWM_ENABLE ; 
 int PWM_PERIOD ; 
 int PWM_SHOW_CONFIG ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_ioctls_limit (int,unsigned long const*,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_limit_stdio () ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 char* device_name ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int ioctl (int,unsigned long const,struct pwm_state*) ; 
 int /*<<< orphan*/  nitems (unsigned long const*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  set_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct pwm_state state;
	int fd;
	int period, duty;
	int action, ch;
	cap_rights_t right_ioctl;
	const unsigned long pwm_ioctls[] = {PWMGETSTATE, PWMSETSTATE};
	char *percent;
	bool setname;

	action = 0;
	setname = false;
	fd = -1;
	period = duty = -1;

	while ((ch = getopt(argc, argv, "f:EDCp:d:")) != -1) {
		switch (ch) {
		case 'E':
			if (action & (PWM_DISABLE | PWM_SHOW_CONFIG))
				usage();
			action |= PWM_ENABLE;
			break;
		case 'D':
			if (action & (PWM_ENABLE | PWM_SHOW_CONFIG))
				usage();
			action |= PWM_DISABLE;
			break;
		case 'C':
			if (action)
				usage();
			action = PWM_SHOW_CONFIG;
			break;
		case 'p':
			if (action & PWM_SHOW_CONFIG)
				usage();
			action |= PWM_PERIOD;
			period = strtol(optarg, NULL, 10);
			break;
		case 'd':
			if (action & PWM_SHOW_CONFIG)
				usage();
			action |= PWM_DUTY;
			duty = strtol(optarg, &percent, 10);
			if (*percent == '%') {
				if (duty < 0 || duty > 100) {
					fprintf(stderr, 
					    "Invalid duty percentage\n");
					usage();
				}
			} else if (*percent != '\0')
				usage();
			break;
		case 'f':
			setname = true;
			set_device_name(optarg);
			break;
		case '?':
			usage();
			break;
		}
	}

	if (action == 0)
		usage();

	if ((fd = open(device_name, O_RDWR)) == -1) {
		fprintf(stderr, "pwm: cannot open %s: %s\n",
		    device_name, strerror(errno));
		if (setname)
			exit(1);
		else
			usage();
	}

	if (caph_limit_stdio() < 0) {
		fprintf(stderr, "can't limit stdio rights");
		goto fail;
	}
	caph_cache_catpages();
	cap_rights_init(&right_ioctl, CAP_IOCTL);
	if (caph_rights_limit(fd, &right_ioctl) < 0) {
		fprintf(stderr, "cap_right_limit() failed\n");
		goto fail;
	}
	if (caph_ioctls_limit(fd, pwm_ioctls, nitems(pwm_ioctls)) < 0) {
		fprintf(stderr, "caph_ioctls_limit() failed\n");
		goto fail;
	}
	if (caph_enter() < 0) {
		fprintf(stderr, "failed to enter capability mode\n");
		goto fail;
	}

	/* Fill the common args */
	if (ioctl(fd, PWMGETSTATE, &state) == -1) {
		fprintf(stderr, "Cannot get current state of the pwm controller\n");
		goto fail;
	}

	if (action == PWM_SHOW_CONFIG) {
		printf("period: %u\nduty: %u\nenabled:%d\n",
		    state.period,
		    state.duty,
		    state.enable);
		goto fail;
	} else {
		if (action & PWM_ENABLE)
			state.enable = true;
		if (action & PWM_DISABLE)
			state.enable = false;
		if (action & PWM_PERIOD)
			state.period = period;
		if (action & PWM_DUTY) {
			if (*percent != '\0')
				state.duty = state.period * duty / 100;
			else
				state.duty = duty;
		}
	
		if (ioctl(fd, PWMSETSTATE, &state) == -1) {
			fprintf(stderr,
			  "Cannot configure the pwm controller\n");
			goto fail;
		}
	}

	close(fd);
	return (0);

fail:
	close(fd);
	return (1);
}