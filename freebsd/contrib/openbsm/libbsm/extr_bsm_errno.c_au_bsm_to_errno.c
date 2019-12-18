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
typedef  int /*<<< orphan*/  u_char ;
struct bsm_errno {int be_local_errno; } ;

/* Variables and functions */
 int ERRNO_NO_LOCAL_MAPPING ; 
 struct bsm_errno* bsm_lookup_errno_bsm (int /*<<< orphan*/ ) ; 

int
au_bsm_to_errno(u_char bsm_errno, int *errorp)
{
	const struct bsm_errno *bsme;

	bsme = bsm_lookup_errno_bsm(bsm_errno);
	if (bsme == NULL || bsme->be_local_errno == ERRNO_NO_LOCAL_MAPPING)
		return (-1);
	*errorp = bsme->be_local_errno;
	return (0);
}