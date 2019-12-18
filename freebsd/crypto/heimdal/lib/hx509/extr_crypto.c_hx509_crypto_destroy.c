#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_crypto ;
struct TYPE_6__ {TYPE_2__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  oid; struct TYPE_7__* param; TYPE_1__ key; struct TYPE_7__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
hx509_crypto_destroy(hx509_crypto crypto)
{
    if (crypto->name)
	free(crypto->name);
    if (crypto->key.data)
	free(crypto->key.data);
    if (crypto->param)
	free(crypto->param);
    der_free_oid(&crypto->oid);
    memset(crypto, 0, sizeof(*crypto));
    free(crypto);
}