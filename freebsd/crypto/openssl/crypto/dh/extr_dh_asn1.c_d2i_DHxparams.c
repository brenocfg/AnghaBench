#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* vparams; TYPE_9__* seed; int /*<<< orphan*/  counter; int /*<<< orphan*/  j; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ int_dhx942_dh ;
struct TYPE_12__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {int /*<<< orphan*/  counter; int /*<<< orphan*/  seedlen; int /*<<< orphan*/ * seed; int /*<<< orphan*/  j; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
typedef  TYPE_2__ DH ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING_free (TYPE_9__*) ; 
 int /*<<< orphan*/  DH_free (TYPE_2__*) ; 
 TYPE_2__* DH_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* d2i_int_dhx (int /*<<< orphan*/ *,unsigned char const**,long) ; 

DH *d2i_DHxparams(DH **a, const unsigned char **pp, long length)
{
    int_dhx942_dh *dhx = NULL;
    DH *dh = NULL;
    dh = DH_new();
    if (dh == NULL)
        return NULL;
    dhx = d2i_int_dhx(NULL, pp, length);
    if (dhx == NULL) {
        DH_free(dh);
        return NULL;
    }

    if (a) {
        DH_free(*a);
        *a = dh;
    }

    dh->p = dhx->p;
    dh->q = dhx->q;
    dh->g = dhx->g;
    dh->j = dhx->j;

    if (dhx->vparams) {
        dh->seed = dhx->vparams->seed->data;
        dh->seedlen = dhx->vparams->seed->length;
        dh->counter = dhx->vparams->counter;
        dhx->vparams->seed->data = NULL;
        ASN1_BIT_STRING_free(dhx->vparams->seed);
        OPENSSL_free(dhx->vparams);
        dhx->vparams = NULL;
    }

    OPENSSL_free(dhx);
    return dh;
}