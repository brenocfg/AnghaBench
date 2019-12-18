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
typedef  int /*<<< orphan*/  FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int FTS_NOCHDIR ; 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
 scalar_t__ fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_compare ; 
 int /*<<< orphan*/ * fts_open (char* const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fts_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fts_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
main(void)
{
	const char	*argv[2];
	FTS		*ftsp;
	FTSENT		*entry;

	argv[0] = ".";
	argv[1] = (char *)NULL;

	ftsp = fts_open((char * const *)argv,
	    FTS_PHYSICAL | FTS_NOCHDIR, fts_compare);

	if (ftsp == NULL) {
		perror("fts_open");
		return 1;
	}

	entry = fts_read(ftsp);

	if (entry == NULL) {
		perror("fts_read");
		return 1;
	}

	if (fts_set(ftsp, entry, FTS_SKIP) != 0) {
		perror("fts_set");
		return 1;
	}

	if (fts_close(ftsp) != 0) {
		perror("fts_close");
		return 1;
	}

	return 0;
}