#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int set_inactive; int set_active; int has_bootnum; int delete; int copy; int create; int dry_run; int delete_bootnext; int set_bootnext; int once; int del_timeout; int set_timeout; int verbose; void* order; void* loader; void* timeout; void* label; void* kernel; void* env; void* cp_src; void* bootnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_USAGE ; 
 int /*<<< orphan*/  BOOTNEXT_USAGE ; 
 int /*<<< orphan*/  CREATE_USAGE ; 
 int /*<<< orphan*/  DELETE_USAGE ; 
 int /*<<< orphan*/  ORDER_USAGE ; 
 int /*<<< orphan*/  USAGE ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lopts ; 
 void* mangle_loader (void*) ; 
 int /*<<< orphan*/  optarg ; 
 TYPE_1__ opts ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 void* strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
parse_args(int argc, char *argv[])
{
	int ch;

	while ((ch = getopt_long(argc, argv, "AaBb:C:cDe:hk:L:l:NnOo:Tt:v",
		    lopts, NULL)) != -1) {
		switch (ch) {
		case 'A':
			opts.set_inactive = true;
			break;
		case 'a':
			opts.set_active = true;
			break;
		case 'b':
			opts.has_bootnum = true;
			opts.bootnum = strtoul(optarg, NULL, 16);
			break;
		case 'B':
			opts.delete = true;
			break;
		case 'C':
			opts.copy = true;
			opts.cp_src = strtoul(optarg, NULL, 16);
		case 'c':
			opts.create = true;
			break;
		case 'D': /* should be remove dups XXX */
			opts.dry_run = true;
			break;
		case 'e':
			free(opts.env);
			opts.env = strdup(optarg);
			break;
		case 'h':
		default:
			errx(1, "%s", USAGE);
			break;
		case 'k':
			free(opts.kernel);
			opts.kernel = strdup(optarg);
			break;
		case 'L':
			free(opts.label);
			opts.label = strdup(optarg);
			break;
		case 'l':
			free(opts.loader);
			opts.loader = strdup(optarg);
			opts.loader = mangle_loader(opts.loader);
			break;
		case 'N':
			opts.delete_bootnext = true;
			break;
		case 'n':
			opts.set_bootnext = true;
			break;
		case 'O':
			opts.once = true;
			break;
		case 'o':
			free(opts.order);
			opts.order = strdup(optarg);
			break;
		case 'T':
			opts.del_timeout = true;
			break;
		case 't':
			opts.set_timeout = true;
			opts.timeout = strtoul(optarg, NULL, 10);
			break;
		case 'v':
			opts.verbose = true;
			break;
		}
	}
	if (opts.create) {
		if (!opts.loader)
			errx(1, "%s",CREATE_USAGE);
		return;
	}

	if (opts.order && !(opts.order))
		errx(1, "%s", ORDER_USAGE);

	if ((opts.set_inactive || opts.set_active) && !opts.has_bootnum)
		errx(1, "%s", ACTIVE_USAGE);

	if (opts.delete && !opts.has_bootnum)
		errx(1, "%s", DELETE_USAGE);

	if (opts.set_bootnext && !opts.has_bootnum)
		errx(1, "%s", BOOTNEXT_USAGE);
}