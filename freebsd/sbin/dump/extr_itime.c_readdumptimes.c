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
struct dumptime {int /*<<< orphan*/  dt_value; } ;
struct dumpdates {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct dumptime* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dumptime*,int /*<<< orphan*/ ) ; 
 struct dumptime* SLIST_NEXT (struct dumptime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** calloc (unsigned int,int) ; 
 int /*<<< orphan*/ ** ddatev ; 
 int /*<<< orphan*/  dt_list ; 
 int /*<<< orphan*/  dthead ; 
 int /*<<< orphan*/  free (struct dumptime*) ; 
 scalar_t__ getrecord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nddates ; 

__attribute__((used)) static void
readdumptimes(FILE *df)
{
	int i;
	struct	dumptime *dtwalk;

	for (;;) {
		dtwalk = (struct dumptime *)calloc(1, sizeof (struct dumptime));
		if (getrecord(df, &(dtwalk->dt_value)) < 0) {
			free(dtwalk);
			break;
		}
		nddates++;
		SLIST_INSERT_HEAD(&dthead, dtwalk, dt_list);
	}

	/*
	 *	arrayify the list, leaving enough room for the additional
	 *	record that we may have to add to the ddate structure
	 */
	ddatev = calloc((unsigned) (nddates + 1), sizeof (struct dumpdates *));
	dtwalk = SLIST_FIRST(&dthead);
	for (i = nddates - 1; i >= 0; i--, dtwalk = SLIST_NEXT(dtwalk, dt_list))
		ddatev[i] = &dtwalk->dt_value;
}