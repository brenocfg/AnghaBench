#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  _save; } ;
struct TYPE_6__ {TYPE_1__ tbsCertificate; int /*<<< orphan*/  signatureAlgorithm; int /*<<< orphan*/  signatureValue; } ;
typedef  TYPE_2__ Certificate ;

/* Variables and functions */
 int _hx509_AlgorithmIdentifier_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int der_heim_bit_string_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int der_heim_octet_string_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
_hx509_Certificate_cmp(const Certificate *p, const Certificate *q)
{
    int diff;
    diff = der_heim_bit_string_cmp(&p->signatureValue, &q->signatureValue);
    if (diff)
	return diff;
    diff = _hx509_AlgorithmIdentifier_cmp(&p->signatureAlgorithm,
					  &q->signatureAlgorithm);
    if (diff)
	return diff;
    diff = der_heim_octet_string_cmp(&p->tbsCertificate._save,
				     &q->tbsCertificate._save);
    return diff;
}