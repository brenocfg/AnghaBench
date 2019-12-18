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
struct pollfd {int /*<<< orphan*/  events; scalar_t__ fd; } ;
struct fifolog_writer {int dummy; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  POLLIN ; 
 unsigned int Z_BEST_COMPRESSION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifolog_write_close (struct fifolog_writer*) ; 
 struct fifolog_writer* fifolog_write_new () ; 
 char* fifolog_write_open (struct fifolog_writer*,char* const,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fifolog_write_poll (struct fifolog_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifolog_write_record_poll (struct fifolog_writer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char* const*,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 unsigned int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char * const *argv)
{
	struct fifolog_writer *f;
	const char *es;
	struct pollfd pfd[1];
	char buf[BUFSIZ], *p;
	int i, c;
	unsigned w_opt = 10;
	unsigned s_opt = 60;
	unsigned z_opt = Z_BEST_COMPRESSION;

	while ((c = getopt(argc, argv, "w:s:z:")) != -1) {
		switch(c) {
		case 'w':
			w_opt = strtoul(optarg, NULL, 0);
			break;
		case 's':
			s_opt = strtoul(optarg, NULL, 0);
			break;
		case 'z':
			z_opt = strtoul(optarg, NULL, 0);
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc != 1)
		usage();

	if (z_opt > 9)
		usage();

	if (w_opt > s_opt)
		usage();

	f = fifolog_write_new();
	assert(f != NULL);

	es = fifolog_write_open(f, argv[0], w_opt, s_opt, z_opt);
	if (es)
		err(1, "Error: %s", es);

	while (1) {
		pfd[0].fd = 0;
		pfd[0].events = POLLIN;
		i = poll(pfd, 1, 1000);
		if (i == 1) {
			if (fgets(buf, sizeof buf, stdin) == NULL)
				break;
			p = strchr(buf, '\0');
			assert(p != NULL);
			while (p > buf && isspace(p[-1]))
				p--;
			*p = '\0';
			if (*buf != '\0')
				fifolog_write_record_poll(f, 0, 0, buf, 0);
		} else if (i == 0)
			fifolog_write_poll(f, 0);
	}
	fifolog_write_close(f);
	return (0);
}