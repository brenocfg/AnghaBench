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
typedef  int /*<<< orphan*/  CK_RV ;
typedef  int /*<<< orphan*/ * CK_MECHANISM_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_DEVICE_MEMORY ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int) ; 

__attribute__((used)) static CK_RV
dup_mechanism(CK_MECHANISM_PTR *dp, const CK_MECHANISM_PTR pMechanism)
{
    CK_MECHANISM_PTR p;

    p = malloc(sizeof(*p));
    if (p == NULL)
	return CKR_DEVICE_MEMORY;

    if (*dp)
	free(*dp);
    *dp = p;
    memcpy(p, pMechanism, sizeof(*p));

    return CKR_OK;
}