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
struct sockopt {size_t sopt_valsize; int /*<<< orphan*/  sopt_val; int /*<<< orphan*/ * sopt_td; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,size_t) ; 
 int copyin (int /*<<< orphan*/ ,void*,size_t) ; 

int
sooptcopyin(struct sockopt *sopt, void *buf, size_t len, size_t minlen)
{
	size_t	valsize;

	/*
	 * If the user gives us more than we wanted, we ignore it, but if we
	 * don't get the minimum length the caller wants, we return EINVAL.
	 * On success, sopt->sopt_valsize is set to however much we actually
	 * retrieved.
	 */
	if ((valsize = sopt->sopt_valsize) < minlen)
		return EINVAL;
	if (valsize > len)
		sopt->sopt_valsize = valsize = len;

	if (sopt->sopt_td != NULL)
		return (copyin(sopt->sopt_val, buf, valsize));

	bcopy(sopt->sopt_val, buf, valsize);
	return (0);
}