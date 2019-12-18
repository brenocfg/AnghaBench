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
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ X509_EXTENSION ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int X509_EXTENSION_set_data(X509_EXTENSION *ex, ASN1_OCTET_STRING *data)
{
    int i;

    if (ex == NULL)
        return 0;
    i = ASN1_OCTET_STRING_set(&ex->value, data->data, data->length);
    if (!i)
        return 0;
    return 1;
}