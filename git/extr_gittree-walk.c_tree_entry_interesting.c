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
struct strbuf {int dummy; } ;
struct pathspec {int magic; } ;
struct name_entry {int /*<<< orphan*/  mode; } ;
struct index_state {int dummy; } ;
typedef  enum interesting { ____Placeholder_interesting } interesting ;

/* Variables and functions */
 int PATHSPEC_EXCLUDE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int all_entries_interesting ; 
 int all_entries_not_interesting ; 
 int do_match (struct index_state*,struct name_entry const*,struct strbuf*,int,struct pathspec const*,int) ; 
 int entry_interesting ; 
 int entry_not_interesting ; 

enum interesting tree_entry_interesting(struct index_state *istate,
					const struct name_entry *entry,
					struct strbuf *base, int base_offset,
					const struct pathspec *ps)
{
	enum interesting positive, negative;
	positive = do_match(istate, entry, base, base_offset, ps, 0);

	/*
	 * case | entry | positive | negative | result
	 * -----+-------+----------+----------+-------
	 *   1  |  file |   -1     |  -1..2   |  -1
	 *   2  |  file |    0     |  -1..2   |   0
	 *   3  |  file |    1     |   -1     |   1
	 *   4  |  file |    1     |    0     |   1
	 *   5  |  file |    1     |    1     |   0
	 *   6  |  file |    1     |    2     |   0
	 *   7  |  file |    2     |   -1     |   2
	 *   8  |  file |    2     |    0     |   1
	 *   9  |  file |    2     |    1     |   0
	 *  10  |  file |    2     |    2     |  -1
	 * -----+-------+----------+----------+-------
	 *  11  |  dir  |   -1     |  -1..2   |  -1
	 *  12  |  dir  |    0     |  -1..2   |   0
	 *  13  |  dir  |    1     |   -1     |   1
	 *  14  |  dir  |    1     |    0     |   1
	 *  15  |  dir  |    1     |    1     |   1 (*)
	 *  16  |  dir  |    1     |    2     |   0
	 *  17  |  dir  |    2     |   -1     |   2
	 *  18  |  dir  |    2     |    0     |   1
	 *  19  |  dir  |    2     |    1     |   1 (*)
	 *  20  |  dir  |    2     |    2     |  -1
	 *
	 * (*) An exclude pattern interested in a directory does not
	 * necessarily mean it will exclude all of the directory. In
	 * wildcard case, it can't decide until looking at individual
	 * files inside. So don't write such directories off yet.
	 */

	if (!(ps->magic & PATHSPEC_EXCLUDE) ||
	    positive <= entry_not_interesting) /* #1, #2, #11, #12 */
		return positive;

	negative = do_match(istate, entry, base, base_offset, ps, 1);

	/* #8, #18 */
	if (positive == all_entries_interesting &&
	    negative == entry_not_interesting)
		return entry_interesting;

	/* #3, #4, #7, #13, #14, #17 */
	if (negative <= entry_not_interesting)
		return positive;

	/* #15, #19 */
	if (S_ISDIR(entry->mode) &&
	    positive >= entry_interesting &&
	    negative == entry_interesting)
		return entry_interesting;

	if ((positive == entry_interesting &&
	     negative >= entry_interesting) || /* #5, #6, #16 */
	    (positive == all_entries_interesting &&
	     negative == entry_interesting)) /* #9 */
		return entry_not_interesting;

	return all_entries_not_interesting; /* #10, #20 */
}