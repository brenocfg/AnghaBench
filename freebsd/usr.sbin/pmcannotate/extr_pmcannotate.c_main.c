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
typedef  int /*<<< orphan*/  tmpf ;
struct entry {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FATAL (char*,char*,char*) ; 
 int FNBUFF ; 
 int F_OK ; 
 int LNBUFF ; 
 int MAXPATHLEN ; 
 int R_OK ; 
 int /*<<< orphan*/  TMPNAME ; 
 char* _PATH_TMP ; 
 int access (char*,int) ; 
 int /*<<< orphan*/  asmparse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ atof (char*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int cparse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry_acqref (struct entry*) ; 
 struct entry* entry_create (char*,uintptr_t,uintptr_t,uintptr_t) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fqueue_compact (float) ; 
 int fqueue_getall (char*,char*,int) ; 
 int fqueue_insertgen () ; 
 struct entry* general_findent (uintptr_t) ; 
 int /*<<< orphan*/  general_insertent (struct entry*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ isspace (char) ; 
 int mkstemp (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int remove (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 int sscanf (char*,char*,void**,char*,void**,void**) ; 
 scalar_t__ system (char*) ; 
 int /*<<< orphan*/  totalsamples ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	char buffer[LNBUFF], fname[FNBUFF];
	char *tbfl, *tofl, *tmpdir;
	char tmpf[MAXPATHLEN * 2 + 50];
	float limit;
	char *bin, *exec, *kfile, *ofile;
	struct entry *obj;
	FILE *gfp, *bfp;
	void *ptr, *hstart, *hend;
	uintptr_t tmppc, ostart, oend;
	int cget, asmsrc;

	exec = argv[0];
	ofile = NULL;
	bin = NULL;
	kfile = NULL;
	asmsrc = 0;
	limit = 0.5;
	while ((cget = getopt(argc, argv, "ahl:k:")) != -1)
		switch(cget) {
		case 'a':
			asmsrc = 1;
			break;
		case 'k':
			kfile = optarg;
			break;
		case 'l':
			limit = (float)atof(optarg);
			break;
		case 'h':
		case '?':
		default:
			usage(exec);
		}
	argc -= optind;
	argv += optind;
	if (argc != 2)
		usage(exec);
	ofile = argv[0];
	bin = argv[1];

	if (access(bin, R_OK | F_OK) == -1)
		FATAL(exec, "%s: Impossible to locate the binary file\n",
		    exec);
	if (access(ofile, R_OK | F_OK) == -1)
		FATAL(exec, "%s: Impossible to locate the pmcstat file\n",
		    exec);
	if (kfile != NULL && access(kfile, R_OK | F_OK) == -1)
		FATAL(exec, "%s: Impossible to locate the kernel file\n",
		    exec);

	bzero(tmpf, sizeof(tmpf));
	tmpdir = getenv("TMPDIR");
	if (tmpdir == NULL) {
		asprintf(&tbfl, "%s/%s", _PATH_TMP, TMPNAME);
		asprintf(&tofl, "%s/%s", _PATH_TMP, TMPNAME);
	} else {
		asprintf(&tbfl, "%s/%s", tmpdir, TMPNAME);
		asprintf(&tofl, "%s/%s", tmpdir, TMPNAME);
	}
	if (tofl == NULL || tbfl == NULL)
		FATAL(exec, "%s: Cannot create tempfile templates\n",
		    exec);
	if (mkstemp(tofl) == -1)
		FATAL(exec, "%s: Impossible to create the tmp file\n",
		    exec);
	if (kfile != NULL)
		snprintf(tmpf, sizeof(tmpf), "pmcstat -k %s -R %s -m %s",
		    kfile, ofile, tofl);
	else
		snprintf(tmpf, sizeof(tmpf), "pmcstat -R %s -m %s", ofile,
		    tofl);
	if (system(tmpf) != 0)
		FATAL(exec, "%s: Impossible to create the tmp file\n",
		    exec);

	gfp = fopen(tofl, "r");
	if (gfp == NULL)
		FATAL(exec, "%s: Impossible to open the map file\n",
		    exec);

	/*
	 * Make the collection of raw entries from a pmcstat mapped file.
	 * The heuristic here wants strings in the form:
	 * "addr funcname startfaddr endfaddr".
	 */
	while (fgets(buffer, LNBUFF, gfp) != NULL) {
		if (isspace(buffer[0]))
			continue;
		if (sscanf(buffer, "%p %s %p %p\n", &ptr, fname,
		    &hstart, &hend) != 4)
			FATAL(NULL,
			    "%s: Invalid scan of function in the map file\n",
			    exec);
		ostart = (uintptr_t)hstart;
		oend = (uintptr_t)hend;
		tmppc = (uintptr_t)ptr;
		totalsamples++;
		obj = general_findent(tmppc);
		if (obj != NULL) {
			entry_acqref(obj);
			continue;
		}
		obj = entry_create(fname, tmppc, ostart, oend);
		if (obj == NULL)
			FATAL(exec,
			    "%s: Impossible to create a new object\n", exec);
		general_insertent(obj);
	}
	if (fclose(gfp) == EOF)
		FATAL(exec, "%s: Impossible to close the filedesc\n",
		    exec);
	if (remove(tofl) == -1)
                FATAL(exec, "%s: Impossible to remove the tmpfile\n",
                    exec);

	/*
	 * Remove the loose end objects and feed the first-level aggregation
	 * queue.
	 */
	if (fqueue_insertgen() == -1)
		FATAL(exec, "%s: Impossible to generate an analysis\n",
		    exec);
	fqueue_compact(limit);
	if (fqueue_getall(bin, tbfl, asmsrc) == -1)
		FATAL(exec, "%s: Impossible to create the tmp file\n",
		    exec);

	bfp = fopen(tbfl, "r");
	if (bfp == NULL)
		FATAL(exec, "%s: Impossible to open the binary file\n",
		    exec);

	if (asmsrc != 0)
		asmparse(bfp);
	else if (cparse(bfp) == -1)
		FATAL(NULL, "%s: Invalid format for the C file\n", exec);
	if (fclose(bfp) == EOF)
                FATAL(exec, "%s: Impossible to close the filedesc\n",
                    exec);
	if (remove(tbfl) == -1)
                FATAL(exec, "%s: Impossible to remove the tmpfile\n",
                    exec);
	return (0);
}