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
 int /*<<< orphan*/  BCMFW ; 
 int LOG_NDELAY ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_USER ; 
 scalar_t__ bcmfw_check_device (char*) ; 
 scalar_t__ bcmfw_load_firmware (char*,char*,char*) ; 
 int /*<<< orphan*/  bcmfw_usage () ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* optarg ; 

int
main(int argc, char *argv[])
{
	char	*name = NULL, *md = NULL, *fw = NULL;
	int	 x;

	while ((x = getopt(argc, argv, "f:hn:m:")) != -1) {
		switch (x) {
		case 'f': /* firmware file */
			fw = optarg;
			break;

		case 'n': /* name */
			name = optarg;
			break;

		case 'm': /* Mini-driver */
			md = optarg;
			break;

		case 'h':
		default:
			bcmfw_usage();
			/* NOT REACHED */
		}
	}

	if (name == NULL || md == NULL || fw == NULL)
		bcmfw_usage();
		/* NOT REACHED */

	openlog(BCMFW, LOG_NDELAY|LOG_PERROR|LOG_PID, LOG_USER);

	if (bcmfw_check_device(name) < 0)
		exit(1);

	if (bcmfw_load_firmware(name, md, fw) < 0)
		exit(1);

	closelog();

	return (0);
}