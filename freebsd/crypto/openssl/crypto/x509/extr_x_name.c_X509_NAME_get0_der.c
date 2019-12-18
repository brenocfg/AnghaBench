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
struct TYPE_6__ {TYPE_1__* bytes; } ;
typedef  TYPE_2__ X509_NAME ;
struct TYPE_5__ {size_t length; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ i2d_X509_NAME (TYPE_2__*,int /*<<< orphan*/ *) ; 

int X509_NAME_get0_der(X509_NAME *nm, const unsigned char **pder,
                       size_t *pderlen)
{
    /* Make sure encoding is valid */
    if (i2d_X509_NAME(nm, NULL) <= 0)
        return 0;
    if (pder != NULL)
        *pder = (unsigned char *)nm->bytes->data;
    if (pderlen != NULL)
        *pderlen = nm->bytes->length;
    return 1;
}