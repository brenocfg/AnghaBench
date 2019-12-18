#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ATTRIBUTE ;
struct TYPE_3__ {int /*<<< orphan*/  unsignedAttrs; } ;
typedef  TYPE_1__ CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * X509at_get_attr (int /*<<< orphan*/ ,int) ; 

X509_ATTRIBUTE *CMS_unsigned_get_attr(const CMS_SignerInfo *si, int loc)
{
    return X509at_get_attr(si->unsignedAttrs, loc);
}