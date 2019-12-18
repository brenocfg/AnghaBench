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
typedef  TYPE_2__* hx509_crypto ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_octet_string ;
struct TYPE_6__ {TYPE_1__* cipher; } ;
struct TYPE_5__ {int (* set_params ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ *) ; 

int
hx509_crypto_set_params(hx509_context context,
			hx509_crypto crypto,
			const heim_octet_string *param,
			heim_octet_string *ivec)
{
    return (*crypto->cipher->set_params)(context, param, crypto, ivec);
}