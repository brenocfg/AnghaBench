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
typedef  int /*<<< orphan*/  uint64_t ;
struct camdd_io_opts {scalar_t__ dev_type; } ;
typedef  int /*<<< orphan*/  camdd_argmask ;

/* Variables and functions */
 int /*<<< orphan*/  CAMDD_ARG_ERR_RECOVER ; 
 int /*<<< orphan*/  CAMDD_ARG_NONE ; 
 int /*<<< orphan*/  CAMDD_ARG_RETRIES ; 
 int /*<<< orphan*/  CAMDD_ARG_TIMEOUT ; 
 int /*<<< orphan*/  CAMDD_ARG_VERBOSE ; 
 scalar_t__ CAMDD_DEV_NONE ; 
 int CAMDD_PASS_RW_TIMEOUT ; 
 struct camdd_io_opts* calloc (int,int) ; 
 int camdd_parse_io_opts (int /*<<< orphan*/ ,int,struct camdd_io_opts*) ; 
 int camdd_rw (struct camdd_io_opts*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int expand_number (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct camdd_io_opts*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,...) ; 

int
main(int argc, char **argv)
{
	int c;
	camdd_argmask arglist = CAMDD_ARG_NONE;
	int timeout = 0, retry_count = 1;
	int error = 0;
	uint64_t max_io = 0;
	struct camdd_io_opts *opt_list = NULL;

	if (argc == 1) {
		usage();
		exit(1);
	}

	opt_list = calloc(2, sizeof(struct camdd_io_opts));
	if (opt_list == NULL) {
		warn("Unable to allocate option list");
		error = 1;
		goto bailout;
	}

	while ((c = getopt(argc, argv, "C:Ehi:m:o:t:v")) != -1){
		switch (c) {
		case 'C':
			retry_count = strtol(optarg, NULL, 0);
			if (retry_count < 0)
				errx(1, "retry count %d is < 0",
				     retry_count);
			arglist |= CAMDD_ARG_RETRIES;
			break;
		case 'E':
			arglist |= CAMDD_ARG_ERR_RECOVER;
			break;
		case 'i':
		case 'o':
			if (((c == 'i')
			  && (opt_list[0].dev_type != CAMDD_DEV_NONE))
			 || ((c == 'o')
			  && (opt_list[1].dev_type != CAMDD_DEV_NONE))) {
				errx(1, "Only one input and output path "
				    "allowed");
			}
			error = camdd_parse_io_opts(optarg, (c == 'o') ? 1 : 0,
			    (c == 'o') ? &opt_list[1] : &opt_list[0]);
			if (error != 0)
				goto bailout;
			break;
		case 'm':
			error = expand_number(optarg, &max_io);
			if (error == -1) {
				warn("invalid maximum I/O amount %s", optarg);
				error = 1;
				goto bailout;
			}
			break;
		case 't':
			timeout = strtol(optarg, NULL, 0);
			if (timeout < 0)
				errx(1, "invalid timeout %d", timeout);
			/* Convert the timeout from seconds to ms */
			timeout *= 1000;
			arglist |= CAMDD_ARG_TIMEOUT;
			break;
		case 'v':
			arglist |= CAMDD_ARG_VERBOSE;
			break;
		case 'h':
		default:
			usage();
			exit(1);
			break; /*NOTREACHED*/
		}
	}

	if ((opt_list[0].dev_type == CAMDD_DEV_NONE)
	 || (opt_list[1].dev_type == CAMDD_DEV_NONE))
		errx(1, "Must specify both -i and -o");

	/*
	 * Set the timeout if the user hasn't specified one.
	 */
	if (timeout == 0)
		timeout = CAMDD_PASS_RW_TIMEOUT;

	error = camdd_rw(opt_list, 2, max_io, retry_count, timeout);

bailout:
	free(opt_list);

	exit(error);
}