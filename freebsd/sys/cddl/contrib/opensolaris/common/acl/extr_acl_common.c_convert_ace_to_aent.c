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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  aclent_t ;
typedef  int /*<<< orphan*/  ace_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cacl_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cacl_realloc (int /*<<< orphan*/ *,int,int) ; 
 int ln_ace_to_aent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
convert_ace_to_aent(ace_t *acebufp, int acecnt, boolean_t isdir,
    uid_t owner, gid_t group, aclent_t **retaclentp, int *retaclcnt)
{
	int error = 0;
	aclent_t *aclentp, *dfaclentp;
	int aclcnt, dfaclcnt;
	int aclsz, dfaclsz;

	error = ln_ace_to_aent(acebufp, acecnt, owner, group,
	    &aclentp, &aclcnt, &dfaclentp, &dfaclcnt, isdir);

	if (error)
		return (error);


	if (dfaclcnt != 0) {
		/*
		 * Slap aclentp and dfaclentp into a single array.
		 */
		aclsz = sizeof (aclent_t) * aclcnt;
		dfaclsz = sizeof (aclent_t) * dfaclcnt;
		aclentp = cacl_realloc(aclentp, aclsz, aclsz + dfaclsz);
		if (aclentp != NULL) {
			(void) memcpy(aclentp + aclcnt, dfaclentp, dfaclsz);
		} else {
			error = ENOMEM;
		}
	}

	if (aclentp) {
		*retaclentp = aclentp;
		*retaclcnt = aclcnt + dfaclcnt;
	}

	if (dfaclentp)
		cacl_free(dfaclentp, dfaclsz);

	return (error);
}