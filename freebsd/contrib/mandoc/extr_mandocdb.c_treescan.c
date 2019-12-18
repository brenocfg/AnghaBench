#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlink {int dform; char* dsec; char* arch; char* name; char* fsec; int gzip; int /*<<< orphan*/  file; } ;
typedef  enum form { ____Placeholder_form } form ;
struct TYPE_4__ {char* fts_path; int fts_info; int fts_level; char* fts_name; int /*<<< orphan*/  fts_statp; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int FORM_CAT ; 
 int FORM_NONE ; 
 int FORM_SRC ; 
#define  FTS_D 131 
#define  FTS_DP 130 
#define  FTS_F 129 
 int FTS_NOCHDIR ; 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
#define  FTS_SL 128 
 int /*<<< orphan*/  HOMEBREWDIR ; 
 scalar_t__ MANDOCLEVEL_SYSERR ; 
 char* MANDOC_DB ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  basedir ; 
 int exitcode ; 
 int /*<<< orphan*/  free (struct mlink*) ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_compare ; 
 int /*<<< orphan*/ * fts_open (char* const*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct mlink* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/  mlink_add (struct mlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int /*<<< orphan*/  say (char const*,char*,...) ; 
 int stat (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_all ; 
 int /*<<< orphan*/  warnings ; 

__attribute__((used)) static int
treescan(void)
{
	char		 buf[PATH_MAX];
	FTS		*f;
	FTSENT		*ff;
	struct mlink	*mlink;
	int		 gzip;
	enum form	 dform;
	char		*dsec, *arch, *fsec, *cp;
	const char	*path;
	const char	*argv[2];

	argv[0] = ".";
	argv[1] = NULL;

	f = fts_open((char * const *)argv, FTS_PHYSICAL | FTS_NOCHDIR,
	    fts_compare);
	if (f == NULL) {
		exitcode = (int)MANDOCLEVEL_SYSERR;
		say("", "&fts_open");
		return 0;
	}

	dsec = arch = NULL;
	dform = FORM_NONE;

	while ((ff = fts_read(f)) != NULL) {
		path = ff->fts_path + 2;
		switch (ff->fts_info) {

		/*
		 * Symbolic links require various sanity checks,
		 * then get handled just like regular files.
		 */
		case FTS_SL:
			if (realpath(path, buf) == NULL) {
				if (warnings)
					say(path, "&realpath");
				continue;
			}
			if (strstr(buf, basedir) != buf
#ifdef HOMEBREWDIR
			    && strstr(buf, HOMEBREWDIR) != buf
#endif
			) {
				if (warnings) say("",
				    "%s: outside base directory", buf);
				continue;
			}
			/* Use logical inode to avoid mpages dupe. */
			if (stat(path, ff->fts_statp) == -1) {
				if (warnings)
					say(path, "&stat");
				continue;
			}
			/* FALLTHROUGH */

		/*
		 * If we're a regular file, add an mlink by using the
		 * stored directory data and handling the filename.
		 */
		case FTS_F:
			if ( ! strcmp(path, MANDOC_DB))
				continue;
			if ( ! use_all && ff->fts_level < 2) {
				if (warnings)
					say(path, "Extraneous file");
				continue;
			}
			gzip = 0;
			fsec = NULL;
			while (fsec == NULL) {
				fsec = strrchr(ff->fts_name, '.');
				if (fsec == NULL || strcmp(fsec+1, "gz"))
					break;
				gzip = 1;
				*fsec = '\0';
				fsec = NULL;
			}
			if (fsec == NULL) {
				if ( ! use_all) {
					if (warnings)
						say(path,
						    "No filename suffix");
					continue;
				}
			} else if ( ! strcmp(++fsec, "html")) {
				if (warnings)
					say(path, "Skip html");
				continue;
			} else if ( ! strcmp(fsec, "ps")) {
				if (warnings)
					say(path, "Skip ps");
				continue;
			} else if ( ! strcmp(fsec, "pdf")) {
				if (warnings)
					say(path, "Skip pdf");
				continue;
			} else if ( ! use_all &&
			    ((dform == FORM_SRC &&
			      strncmp(fsec, dsec, strlen(dsec))) ||
			     (dform == FORM_CAT && strcmp(fsec, "0")))) {
				if (warnings)
					say(path, "Wrong filename suffix");
				continue;
			} else
				fsec[-1] = '\0';

			mlink = mandoc_calloc(1, sizeof(struct mlink));
			if (strlcpy(mlink->file, path,
			    sizeof(mlink->file)) >=
			    sizeof(mlink->file)) {
				say(path, "Filename too long");
				free(mlink);
				continue;
			}
			mlink->dform = dform;
			mlink->dsec = dsec;
			mlink->arch = arch;
			mlink->name = ff->fts_name;
			mlink->fsec = fsec;
			mlink->gzip = gzip;
			mlink_add(mlink, ff->fts_statp);
			continue;

		case FTS_D:
		case FTS_DP:
			break;

		default:
			if (warnings)
				say(path, "Not a regular file");
			continue;
		}

		switch (ff->fts_level) {
		case 0:
			/* Ignore the root directory. */
			break;
		case 1:
			/*
			 * This might contain manX/ or catX/.
			 * Try to infer this from the name.
			 * If we're not in use_all, enforce it.
			 */
			cp = ff->fts_name;
			if (ff->fts_info == FTS_DP) {
				dform = FORM_NONE;
				dsec = NULL;
				break;
			}

			if ( ! strncmp(cp, "man", 3)) {
				dform = FORM_SRC;
				dsec = cp + 3;
			} else if ( ! strncmp(cp, "cat", 3)) {
				dform = FORM_CAT;
				dsec = cp + 3;
			} else {
				dform = FORM_NONE;
				dsec = NULL;
			}

			if (dsec != NULL || use_all)
				break;

			if (warnings)
				say(path, "Unknown directory part");
			fts_set(f, ff, FTS_SKIP);
			break;
		case 2:
			/*
			 * Possibly our architecture.
			 * If we're descending, keep tabs on it.
			 */
			if (ff->fts_info != FTS_DP && dsec != NULL)
				arch = ff->fts_name;
			else
				arch = NULL;
			break;
		default:
			if (ff->fts_info == FTS_DP || use_all)
				break;
			if (warnings)
				say(path, "Extraneous directory part");
			fts_set(f, ff, FTS_SKIP);
			break;
		}
	}

	fts_close(f);
	return 1;
}