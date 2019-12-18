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
struct roff {int dummy; } ;

/* Variables and functions */
 int ROFFNUM_WHITE ; 
 int /*<<< orphan*/  roff_evalnum (struct roff*,int,char const*,int*,int*,int) ; 
 int roff_getnum (char const*,int*,int*,int) ; 

__attribute__((used)) static int
roff_evalpar(struct roff *r, int ln,
	const char *v, int *pos, int *res, int flags)
{

	if ('(' != v[*pos])
		return roff_getnum(v, pos, res, flags);

	(*pos)++;
	if ( ! roff_evalnum(r, ln, v, pos, res, flags | ROFFNUM_WHITE))
		return 0;

	/*
	 * Omission of the closing parenthesis
	 * is an error in validation mode,
	 * but ignored in evaluation mode.
	 */

	if (')' == v[*pos])
		(*pos)++;
	else if (NULL == res)
		return 0;

	return 1;
}