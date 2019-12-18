#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  salttype; } ;
struct pa_info_data {scalar_t__ etype; TYPE_1__ salt; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_octet_string ;
typedef  int /*<<< orphan*/  AS_REQ ;

/* Variables and functions */
 scalar_t__ ENCTYPE_NULL ; 
 scalar_t__ set_paid (struct pa_info_data*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pa_info_data *
pa_pw_or_afs3_salt(krb5_context context,
		   const krb5_principal client,
		   const AS_REQ *asreq,
		   struct pa_info_data *paid,
		   heim_octet_string *data)
{
    krb5_error_code ret;
    if (paid->etype == ENCTYPE_NULL)
	return NULL;
    ret = set_paid(paid, context,
		   paid->etype,
		   paid->salt.salttype,
		   data->data,
		   data->length,
		   NULL);
    if (ret)
	return NULL;
    return paid;
}