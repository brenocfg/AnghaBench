#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ extnValue; } ;
typedef  int /*<<< orphan*/  SubjectKeyIdentifier ;
typedef  TYPE_2__ Extension ;
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int HX509_EXTENSION_NOT_FOUND ; 
 int /*<<< orphan*/  asn1_oid_id_x509_ce_subjectKeyIdentifier ; 
 int decode_SubjectKeyIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 TYPE_2__* find_extension (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
_hx509_find_extension_subject_key_id(const Certificate *issuer,
				     SubjectKeyIdentifier *si)
{
    const Extension *e;
    size_t size;
    size_t i = 0;

    memset(si, 0, sizeof(*si));

    e = find_extension(issuer, &asn1_oid_id_x509_ce_subjectKeyIdentifier, &i);
    if (e == NULL)
	return HX509_EXTENSION_NOT_FOUND;

    return decode_SubjectKeyIdentifier(e->extnValue.data,
				       e->extnValue.length,
				       si, &size);
}