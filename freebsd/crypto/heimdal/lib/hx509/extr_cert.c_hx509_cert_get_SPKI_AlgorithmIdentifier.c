#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_4__* hx509_cert ;
struct TYPE_9__ {TYPE_3__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_7__ {TYPE_1__ subjectPublicKeyInfo; } ;
struct TYPE_8__ {TYPE_2__ tbsCertificate; } ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int copy_AlgorithmIdentifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
hx509_cert_get_SPKI_AlgorithmIdentifier(hx509_context context,
					hx509_cert p,
					AlgorithmIdentifier *alg)
{
    int ret;

    ret = copy_AlgorithmIdentifier(&p->data->tbsCertificate.subjectPublicKeyInfo.algorithm, alg);
    if (ret)
	hx509_set_error_string(context, 0, ret,
			       "Failed to copy SPKI AlgorithmIdentifier");
    return ret;
}