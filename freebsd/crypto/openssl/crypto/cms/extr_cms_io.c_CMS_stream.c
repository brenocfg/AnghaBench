#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* data; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;

/* Variables and functions */
 TYPE_1__* ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_FLAG_CONT ; 
 int /*<<< orphan*/  ASN1_STRING_FLAG_NDEF ; 
 int /*<<< orphan*/  CMS_F_CMS_STREAM ; 
 TYPE_1__** CMS_get0_content (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 

int CMS_stream(unsigned char ***boundary, CMS_ContentInfo *cms)
{
    ASN1_OCTET_STRING **pos;
    pos = CMS_get0_content(cms);
    if (pos == NULL)
        return 0;
    if (*pos == NULL)
        *pos = ASN1_OCTET_STRING_new();
    if (*pos != NULL) {
        (*pos)->flags |= ASN1_STRING_FLAG_NDEF;
        (*pos)->flags &= ~ASN1_STRING_FLAG_CONT;
        *boundary = &(*pos)->data;
        return 1;
    }
    CMSerr(CMS_F_CMS_STREAM, ERR_R_MALLOC_FAILURE);
    return 0;
}