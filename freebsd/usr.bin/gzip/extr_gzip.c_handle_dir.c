#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fts_info; int /*<<< orphan*/  fts_statp; int /*<<< orphan*/  fts_path; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
#define  FTS_D 133 
#define  FTS_DNR 132 
#define  FTS_DP 131 
#define  FTS_ERR 130 
#define  FTS_F 129 
 int FTS_NOCHDIR ; 
#define  FTS_NS 128 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (char**,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
handle_dir(char *dir)
{
	char *path_argv[2];
	FTS *fts;
	FTSENT *entry;

	path_argv[0] = dir;
	path_argv[1] = 0;
	fts = fts_open(path_argv, FTS_PHYSICAL | FTS_NOCHDIR, NULL);
	if (fts == NULL) {
		warn("couldn't fts_open %s", dir);
		return;
	}

	while ((entry = fts_read(fts))) {
		switch(entry->fts_info) {
		case FTS_D:
		case FTS_DP:
			continue;

		case FTS_DNR:
		case FTS_ERR:
		case FTS_NS:
			maybe_warn("%s", entry->fts_path);
			continue;
		case FTS_F:
			handle_file(entry->fts_path, entry->fts_statp);
		}
	}
	(void)fts_close(fts);
}