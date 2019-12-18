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
typedef  int /*<<< orphan*/  recno_t ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ ISBLANK (int /*<<< orphan*/ ) ; 
 scalar_t__ db_eget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int*) ; 

int
nonblank(
	SCR *sp,
	recno_t lno,
	size_t *cnop)
{
	CHAR_T *p;
	size_t cnt, len, off;
	int isempty;

	/* Default. */
	off = *cnop;
	*cnop = 0;

	/* Get the line, succeeding in an empty file. */
	if (db_eget(sp, lno, &p, &len, &isempty))
		return (!isempty);

	/* Set the offset. */
	if (len == 0 || off >= len)
		return (0);

	for (cnt = off, p = &p[off],
	    len -= off; len && ISBLANK(*p); ++cnt, ++p, --len);

	/* Set the return. */
	*cnop = len ? cnt : cnt - 1;
	return (0);
}