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
typedef  int /*<<< orphan*/  const ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  const** cms_get0_econtent_type (int /*<<< orphan*/ *) ; 

const ASN1_OBJECT *CMS_get0_eContentType(CMS_ContentInfo *cms)
{
    ASN1_OBJECT **petype;
    petype = cms_get0_econtent_type(cms);
    if (petype)
        return *petype;
    return NULL;
}