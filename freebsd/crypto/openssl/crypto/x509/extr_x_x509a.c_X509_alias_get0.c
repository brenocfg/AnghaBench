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
struct TYPE_7__ {TYPE_2__* aux; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_6__ {TYPE_1__* alias; } ;
struct TYPE_5__ {int length; unsigned char* data; } ;

/* Variables and functions */

unsigned char *X509_alias_get0(X509 *x, int *len)
{
    if (!x->aux || !x->aux->alias)
        return NULL;
    if (len)
        *len = x->aux->alias->length;
    return x->aux->alias->data;
}