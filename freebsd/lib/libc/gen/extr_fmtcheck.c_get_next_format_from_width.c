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
typedef  int /*<<< orphan*/  EFT ;

/* Variables and functions */
 int /*<<< orphan*/  FMTCHECK_PRECISION ; 
 int /*<<< orphan*/  FMTCHECK_UNKNOWN ; 
 int /*<<< orphan*/  RETURN (char const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_next_format_from_precision (char const**) ; 
 scalar_t__ isdigit (char const) ; 

__attribute__((used)) static EFT
get_next_format_from_width(const char **pf)
{
	const char	*f;

	f = *pf;
	if (*f == '.') {
		f++;
		if (*f == '*') {
			RETURN(pf,f,FMTCHECK_PRECISION);
		}
		/* eat any precision (empty is allowed) */
		while (isdigit(*f)) f++;
		if (!*f) RETURN(pf,f,FMTCHECK_UNKNOWN);
	}
	RETURN(pf,f,get_next_format_from_precision(pf));
	/*NOTREACHED*/
}