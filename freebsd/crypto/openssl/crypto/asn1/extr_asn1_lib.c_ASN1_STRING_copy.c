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
struct TYPE_5__ {int flags; int /*<<< orphan*/  length; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_FLAG_EMBED ; 
 int /*<<< orphan*/  ASN1_STRING_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ASN1_STRING_copy(ASN1_STRING *dst, const ASN1_STRING *str)
{
    if (str == NULL)
        return 0;
    dst->type = str->type;
    if (!ASN1_STRING_set(dst, str->data, str->length))
        return 0;
    /* Copy flags but preserve embed value */
    dst->flags &= ASN1_STRING_FLAG_EMBED;
    dst->flags |= str->flags & ~ASN1_STRING_FLAG_EMBED;
    return 1;
}