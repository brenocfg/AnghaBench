#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* digestedData; } ;
struct TYPE_7__ {TYPE_1__ d; } ;
struct TYPE_6__ {int /*<<< orphan*/  digestAlgorithm; } ;
typedef  TYPE_2__ CMS_DigestedData ;
typedef  TYPE_3__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * cms_DigestAlgorithm_init_bio (int /*<<< orphan*/ ) ; 

BIO *cms_DigestedData_init_bio(CMS_ContentInfo *cms)
{
    CMS_DigestedData *dd;
    dd = cms->d.digestedData;
    return cms_DigestAlgorithm_init_bio(dd->digestAlgorithm);
}