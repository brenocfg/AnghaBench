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
typedef  scalar_t__ uint8_t ;
struct mfi_bbu_properties {unsigned long learn_delay_interval; int auto_learn_mode; char bbu_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ MFI_STAT_OK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ mfi_bbu_get_props (int,struct mfi_bbu_properties*,scalar_t__*) ; 
 scalar_t__ mfi_bbu_set_props (int,struct mfi_bbu_properties*,scalar_t__*) ; 
 int mfi_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mfi_status (scalar_t__) ; 
 int /*<<< orphan*/  mfi_unit ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
update_bbu_props(int ac, char **av)
{
	struct mfi_bbu_properties props;
	unsigned long delay;
	uint8_t status;
	int error, fd;
	char *mode, *endptr;

	status = MFI_STAT_OK;
	error = 0;

	if (ac != 3) {
		warnx("bbu: property and value required");
		return (EINVAL);
	}

	fd = mfi_open(mfi_unit, O_RDWR);
	if (fd < 0) {
		error = errno;
		warn("mfi_open");
		return (error);
	}

	if (mfi_bbu_get_props(fd, &props, &status) < 0) {
		error = errno;
		warn("Failed to get BBU properties");
		goto done;
	} else if (status != MFI_STAT_OK) {
		warnx("Failed to get BBU properties: %s", mfi_status(status));
		error = EIO;
		goto done;
	}

	if (strcmp(av[1], "learn-delay") == 0) {
		delay = strtoul(av[2], &endptr, 10);
		if (strlen(av[2]) == 0 || *endptr != '\0' || delay > 255) {
			warnx("Invalid learn delay '%s'", av[2]);
			error = EINVAL;
			goto done;
		}

		props.learn_delay_interval = delay;
	} else if (strcmp(av[1], "autolearn-mode") == 0) {
		mode = av[2];

		if (strcmp(av[2], "enable") == 0)
			props.auto_learn_mode = 0;
		else if (strcmp(av[2], "disable") == 0)
			props.auto_learn_mode = 1;
		else if (mode[0] >= '0' && mode[0] <= '2' && mode[1] == '\0')
			props.auto_learn_mode = mode[0] - '0';
		else {
			warnx("Invalid mode '%s'", mode);
			error = EINVAL;
			goto done;
		}
	} else if (strcmp(av[1], "bbu-mode") == 0) {
		if (props.bbu_mode == 0) {
			warnx("This BBU does not implement different modes");
			error = EINVAL;
			goto done;
		}

		/* The mode must be an integer between 1 and 5. */
		mode = av[2];
		if (mode[0] < '1' || mode[0] > '5' || mode[1] != '\0') {
			warnx("Invalid mode '%s'", mode);
			error = EINVAL;
			goto done;
		}

		props.bbu_mode = mode[0] - '0';
	} else {
		warnx("bbu: Invalid command '%s'", av[1]);
		error = EINVAL;
		goto done;
	}

	if (mfi_bbu_set_props(fd, &props, &status) < 0) {
		error = errno;
		warn("Failed to set BBU properties");
		goto done;
	} else if (status != MFI_STAT_OK) {
		warnx("Failed to set BBU properties: %s", mfi_status(status));
		error = EIO;
		goto done;
	}

done:
	close(fd);

	return (error);
}