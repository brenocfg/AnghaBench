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
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ ** cms_get0_econtent_type (int /*<<< orphan*/ *) ; 

int CMS_set1_eContentType(CMS_ContentInfo *cms, const ASN1_OBJECT *oid)
{
    ASN1_OBJECT **petype, *etype;
    petype = cms_get0_econtent_type(cms);
    if (!petype)
        return 0;
    if (!oid)
        return 1;
    etype = OBJ_dup(oid);
    if (!etype)
        return 0;
    ASN1_OBJECT_free(*petype);
    *petype = etype;
    return 1;
}