#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_ca_tbs ;
struct TYPE_5__ {int /*<<< orphan*/  subject; int /*<<< orphan*/  issuerUniqueID; int /*<<< orphan*/  subjectUniqueID; int /*<<< orphan*/  crldp; int /*<<< orphan*/  serial; int /*<<< orphan*/  eku; int /*<<< orphan*/  san; int /*<<< orphan*/  spki; } ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_bit_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_heim_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_CRLDistributionPoints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ExtKeyUsage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_GeneralNames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_SubjectPublicKeyInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_ca_tbs_free(hx509_ca_tbs *tbs)
{
    if (tbs == NULL || *tbs == NULL)
	return;

    free_SubjectPublicKeyInfo(&(*tbs)->spki);
    free_GeneralNames(&(*tbs)->san);
    free_ExtKeyUsage(&(*tbs)->eku);
    der_free_heim_integer(&(*tbs)->serial);
    free_CRLDistributionPoints(&(*tbs)->crldp);
    der_free_bit_string(&(*tbs)->subjectUniqueID);
    der_free_bit_string(&(*tbs)->issuerUniqueID);
    hx509_name_free(&(*tbs)->subject);

    memset(*tbs, 0, sizeof(**tbs));
    free(*tbs);
    *tbs = NULL;
}