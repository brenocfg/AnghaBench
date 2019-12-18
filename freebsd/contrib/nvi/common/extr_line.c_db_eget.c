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
typedef  int recno_t ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  db_err (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  db_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ db_last (int /*<<< orphan*/ *,int*) ; 

int
db_eget(
	SCR *sp,
	recno_t lno,				/* Line number. */
	CHAR_T **pp,				/* Pointer store. */
	size_t *lenp,				/* Length store. */
	int *isemptyp)
{
	recno_t l1;

	if (isemptyp != NULL)
		*isemptyp = 0;

	/* If the line exists, simply return it. */
	if (!db_get(sp, lno, 0, pp, lenp))
		return (0);

	/*
	 * If the user asked for line 0 or line 1, i.e. the only possible
	 * line in an empty file, find the last line of the file; db_last
	 * fails loudly.
	 */
	if ((lno == 0 || lno == 1) && db_last(sp, &l1))
		return (1);

	/* If the file isn't empty, fail loudly. */
	if ((lno != 0 && lno != 1) || l1 != 0) {
		db_err(sp, lno);
		return (1);
	}

	if (isemptyp != NULL)
		*isemptyp = 1;

	return (1);
}