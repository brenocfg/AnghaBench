#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int port; void* address; } ;
struct TYPE_5__ {int port; void* address; } ;
struct TYPE_4__ {int listen; int keep; int ssl; } ;
struct options {int max_read; TYPE_3__ dst; TYPE_2__ src; TYPE_1__ extra; } ;
typedef  int /*<<< orphan*/  o ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (struct options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_usage (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static struct options parse_opts(int argc, char **argv)
{
	struct options o;
	int opt;

	memset(&o, 0, sizeof(o));
	o.src.port = o.dst.port = 10024;
	o.max_read = -1;

	while ((opt = getopt(argc, argv, "p:s:R:" "lkSvh")) != -1) {
		switch (opt) {
			case 'p': o.src.port    = atoi(optarg); break;
			case 's': o.src.address = strdup("127.1"); break;
			case 'R': o.max_read    = atoi(optarg); break;

			case 'l': o.extra.listen = 1; break;
			case 'k': o.extra.keep   = 1; break;
			case 'S': o.extra.ssl    = 1; break;

			/**
			 * TODO: implement other bits:
			 * - filters
			 * - pair
			 * - watermarks
			 * - ratelimits
			 */

			case 'v': ++verbose; break;
			case 'h':
				print_usage(stdout, argv[0]);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr, "Unknown option -%c\n", opt); break;
				exit(EXIT_FAILURE);
		}
	}

	if ((argc-optind) > 1) {
		o.dst.address = strdup(argv[optind]);
		++optind;
	}
	if ((argc-optind) > 1) {
		o.dst.port = atoi(optarg);
		++optind;
	}
	if ((argc-optind) > 1) {
		print_usage(stderr, argv[0]);
		exit(1);
	}

	if (!o.src.address)
		o.src.address = strdup("127.1");
	if (!o.dst.address)
		o.dst.address = strdup("127.1");

	return o;
}