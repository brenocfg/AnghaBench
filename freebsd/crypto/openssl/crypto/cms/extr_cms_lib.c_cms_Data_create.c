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
struct TYPE_5__ {int /*<<< orphan*/  contentType; } ;
typedef  TYPE_1__ CMS_ContentInfo ;

/* Variables and functions */
 TYPE_1__* CMS_ContentInfo_new () ; 
 int /*<<< orphan*/  CMS_set_detached (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_pkcs7_data ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 

CMS_ContentInfo *cms_Data_create(void)
{
    CMS_ContentInfo *cms;
    cms = CMS_ContentInfo_new();
    if (cms != NULL) {
        cms->contentType = OBJ_nid2obj(NID_pkcs7_data);
        /* Never detached */
        CMS_set_detached(cms, 0);
    }
    return cms;
}