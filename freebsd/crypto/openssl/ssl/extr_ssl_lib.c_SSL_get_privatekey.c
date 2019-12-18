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
struct TYPE_7__ {TYPE_2__* cert; } ;
struct TYPE_6__ {TYPE_1__* key; } ;
struct TYPE_5__ {int /*<<< orphan*/ * privatekey; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */

EVP_PKEY *SSL_get_privatekey(const SSL *s)
{
    if (s->cert != NULL)
        return s->cert->key->privatekey;
    else
        return NULL;
}