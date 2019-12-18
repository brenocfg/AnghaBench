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
struct TYPE_3__ {scalar_t__ fts_pathlen; int /*<<< orphan*/ * fts_path; } ;
typedef  TYPE_1__ FTS ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reallocf (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
fts_palloc(FTS *sp, size_t more)
{

	sp->fts_pathlen += more + 256;
	/*
	 * Check for possible wraparound.  In an FTS, fts_pathlen is
	 * a signed int but in an FTSENT it is an unsigned short.
	 * We limit fts_pathlen to USHRT_MAX to be safe in both cases.
	 */
	if (sp->fts_pathlen < 0 || sp->fts_pathlen >= USHRT_MAX) {
		if (sp->fts_path)
			free(sp->fts_path);
		sp->fts_path = NULL;
		errno = ENAMETOOLONG;
		return (1);
	}
	sp->fts_path = reallocf(sp->fts_path, sp->fts_pathlen);
	return (sp->fts_path == NULL);
}