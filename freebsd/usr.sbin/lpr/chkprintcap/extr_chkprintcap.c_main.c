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
struct stat {int dummy; } ;
struct skiminfo {int fatalerr; int entries; } ;
struct printer {int /*<<< orphan*/  spool_dir; int /*<<< orphan*/  printer; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  _PATH_PRINTCAP ; 
 int /*<<< orphan*/  check_spool_dirs () ; 
 scalar_t__ errno ; 
 int firstprinter (struct printer*,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ interpret_error (struct printer*,int) ; 
 int /*<<< orphan*/  make_spool_dir (struct printer*) ; 
 int nextprinter (struct printer*,int*) ; 
 int /*<<< orphan*/  note_spool_dir (struct printer*,struct stat*) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int problems ; 
 int /*<<< orphan*/  setprintcap (char*) ; 
 struct skiminfo* skim_printcap (char*,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int,...) ; 

int
main(int argc, char **argv)
{
	struct skiminfo *skres;
	char *pcap_fname;
	int c, error, makedirs, more, queuecnt, verbosity;
	struct printer myprinter, *pp;

	makedirs = 0;
	queuecnt = 0;
	verbosity = 0;
	pcap_fname = NULL;
	pp = &myprinter;

	while ((c = getopt(argc, argv, "df:v")) != -1) {
		switch (c) {
		case 'd':
			makedirs = 1;
			break;

		case 'f':
			pcap_fname = strdup(optarg);
			setprintcap(pcap_fname);
			break;

		case 'v':
			verbosity++;
			break;

		default:
			usage();
		}
	}

	if (optind != argc)
		usage();

	if (pcap_fname == NULL)
		pcap_fname = strdup(_PATH_PRINTCAP);

	/*
	 * Skim through the printcap file looking for simple user-mistakes
	 * which will produce the wrong result for the user, but which may
	 * be pretty hard for the user to notice.  Such user-mistakes will
	 * only generate warning messages.  The (fatal-) problem count will
	 * only be incremented if there is a system problem trying to read
	 * the printcap file.
	*/
	skres = skim_printcap(pcap_fname, verbosity);
	if (skres == NULL) {
		problems = 1;
		goto main_ret;
	} else if (skres->fatalerr) {
		problems = skres->fatalerr;
		goto main_ret;
	}

	/*
	 * Now use the standard capability-db routines to check the values
	 * in each of the queues defined in the printcap file.
	*/
	more = firstprinter(pp, &error);
	if (interpret_error(pp, error) && more)
		goto next;

	while (more) {
		struct stat stab;

		queuecnt++;
		errno = 0;
		if (stat(pp->spool_dir, &stab) < 0) {
			if (errno == ENOENT && makedirs) {
				make_spool_dir(pp);
			} else {
				problems++;
				warn("%s: %s", pp->printer, pp->spool_dir);
			}
		} else {
			note_spool_dir(pp, &stab);
		}

		/* Make other queue-specific validity checks here... */

next:
		more = nextprinter(pp, &error);
		if (interpret_error(pp, error) && more)
			goto next;
	}

	check_spool_dirs();

	if (queuecnt != skres->entries) {
		warnx("WARNING: found %d entries when skimming %s,",
		    skres->entries, pcap_fname);
		warnx("WARNING:  but only found %d queues to process!",
		    queuecnt);
	}

main_ret:
	free(pcap_fname);
	return (problems);
}