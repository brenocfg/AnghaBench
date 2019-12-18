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
typedef  enum nresult { ____Placeholder_nresult } nresult ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 int NUM_ERR ; 
 int NUM_OK ; 
 int NUM_OVER ; 
 int NUM_UNDER ; 
 long STRTOL (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ errno ; 

enum nresult
nget_slong(
	long *valp,
	const CHAR_T *p,
	CHAR_T **endp,
	int base)
{
	errno = 0;
	*valp = STRTOL(p, endp, base);
	if (errno == 0)
		return (NUM_OK);
	if (errno == ERANGE) {
		if (*valp == LONG_MAX)
			return (NUM_OVER);
		if (*valp == LONG_MIN)
			return (NUM_UNDER);
	}
	return (NUM_ERR);
}