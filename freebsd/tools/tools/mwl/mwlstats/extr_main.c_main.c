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
struct mwlstatfoo {int /*<<< orphan*/  (* print_verbose ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* collect_tot ) (struct mwlstatfoo*) ;int /*<<< orphan*/  (* print_total ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update_tot ) (struct mwlstatfoo*) ;int /*<<< orphan*/  (* print_current ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* collect_cur ) (struct mwlstatfoo*) ;int /*<<< orphan*/  (* print_header ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setfmt ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* print_fields ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setifname ) (struct mwlstatfoo*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  S_DEFAULT ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  catchalarm ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 struct mwlstatfoo* mwlstats_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signalled ; 
 int /*<<< orphan*/  sigpause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 int /*<<< orphan*/  stdout ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct mwlstatfoo*) ; 
 int /*<<< orphan*/  stub11 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct mwlstatfoo*) ; 
 int /*<<< orphan*/  stub6 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct mwlstatfoo*) ; 
 int /*<<< orphan*/  stub8 (struct mwlstatfoo*) ; 
 int /*<<< orphan*/  stub9 (struct mwlstatfoo*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	struct mwlstatfoo *wf;
	int c;

	wf = mwlstats_new("mwl0", S_DEFAULT);
	while ((c = getopt(argc, argv, "i:lo:")) != -1) {
		switch (c) {
		case 'i':
			wf->setifname(wf, optarg);
			break;
		case 'l':
			wf->print_fields(wf, stdout);
			return 0;
		case 'o':
			wf->setfmt(wf, optarg);
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