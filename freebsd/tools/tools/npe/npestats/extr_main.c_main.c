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
typedef  int u_long ;
struct npestatfoo {int /*<<< orphan*/  (* print_verbose ) (struct npestatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* collect_tot ) (struct npestatfoo*) ;int /*<<< orphan*/  (* print_total ) (struct npestatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update_tot ) (struct npestatfoo*) ;int /*<<< orphan*/  (* print_current ) (struct npestatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* collect_cur ) (struct npestatfoo*) ;int /*<<< orphan*/  (* print_header ) (struct npestatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setfmt ) (struct npestatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* print_fields ) (struct npestatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setifname ) (struct npestatfoo*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  catchalarm ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getfmt (char*) ; 
 int getopt (int,char**,char*) ; 
 struct npestatfoo* npestats_new (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signalled ; 
 int /*<<< orphan*/  sigpause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 int /*<<< orphan*/  stdout ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct npestatfoo*,char*) ; 
 int /*<<< orphan*/  stub10 (struct npestatfoo*) ; 
 int /*<<< orphan*/  stub11 (struct npestatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct npestatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct npestatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct npestatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct npestatfoo*) ; 
 int /*<<< orphan*/  stub6 (struct npestatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct npestatfoo*) ; 
 int /*<<< orphan*/  stub8 (struct npestatfoo*) ; 
 int /*<<< orphan*/  stub9 (struct npestatfoo*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct npestatfoo *wf;
	const char *ifname;
	int c, banner = 1;

	ifname = getenv("NPE");
	if (ifname == NULL)
		ifname = "npe0";
	wf = npestats_new(ifname, getfmt("default"));
	while ((c = getopt(argc, argv, "bi:lo:z")) != -1) {
		switch (c) {
		case 'b':
			banner = 0;
			break;
		case 'i':
			wf->setifname(wf, optarg);
			break;
		case 'l':
			wf->print_fields(wf, stdout);
			return 0;
		case 'o':
			wf->setfmt(wf, getfmt(optarg));
			break;
		default:
			errx(-1, "usage: %s [-a] [-i ifname] [-l] [-o fmt] [interval]\n", argv[0]);
			/*NOTREACHED*/
		}
	}
	argc -= optind;
	argv += optind;

	if (argc > 0) {
		u_long interval = strtoul(argv[0], NULL, 0);
		int line, omask;

		if (interval < 1)
			interval = 1;
		signal(SIGALRM, catchalarm);
		signalled = 0;
		alarm(interval);
	banner:
		if (banner)
			wf->print_header(wf, stdout);
		line = 0;
	loop:
		if (line != 0) {
			wf->collect_cur(wf);
			wf->print_current(wf, stdout);
			wf->update_tot(wf);
		} else {
			wf->collect_tot(wf);
			wf->print_total(wf, stdout);
		}
		fflush(stdout);
		omask = sigblock(sigmask(SIGALRM));
		if (!signalled)
			sigpause(0);
		sigsetmask(omask);
		signalled = 0;
		alarm(interval);
		line++;
		if (line == 21)		/* XXX tty line count */
			goto banner;
		else
			goto loop;
		/*NOTREACHED*/
	} else {
		wf->collect_tot(wf);
		wf->print_verbose(wf, stdout);
	}
	return 0;
}