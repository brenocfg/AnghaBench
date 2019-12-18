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
struct options {int unlink; int iocp; char* docroot; int /*<<< orphan*/  verbose; int /*<<< orphan*/  unixsock; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  o ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (struct options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_usage (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static struct options
parse_opts(int argc, char **argv)
{
	struct options o;
	int opt;

	memset(&o, 0, sizeof(o));

	while ((opt = getopt(argc, argv, "hp:U:uIv")) != -1) {
		switch (opt) {
			case 'p': o.port = atoi(optarg); break;
			case 'U': o.unixsock = optarg; break;
			case 'u': o.unlink = 1; break;
			case 'I': o.iocp = 1; break;
			case 'v': ++o.verbose; break;
			case 'h': print_usage(stdout, argv[0], 0); break;
			default : fprintf(stderr, "Unknown option %c\n", opt); break;
		}
	}

	if (optind >= argc || (argc - optind) > 1) {
		print_usage(stdout, argv[0], 1);
	}
	o.docroot = argv[optind];

	return o;
}