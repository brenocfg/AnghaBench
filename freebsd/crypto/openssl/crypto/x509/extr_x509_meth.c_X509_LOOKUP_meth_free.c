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
struct TYPE_4__ {struct TYPE_4__* name; } ;
typedef  TYPE_1__ X509_LOOKUP_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void X509_LOOKUP_meth_free(X509_LOOKUP_METHOD *method)
{
    if (method != NULL)
        OPENSSL_free(method->name);
    OPENSSL_free(method);
}