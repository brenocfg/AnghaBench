#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct pa_info_data {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {TYPE_3__ saltvalue; } ;
typedef  TYPE_5__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_21__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ heim_octet_string ;
typedef  int /*<<< orphan*/  e ;
struct TYPE_16__ {size_t len; scalar_t__* val; } ;
struct TYPE_17__ {TYPE_1__ etype; } ;
struct TYPE_23__ {TYPE_2__ req_body; } ;
struct TYPE_22__ {size_t len; TYPE_4__* val; } ;
struct TYPE_19__ {scalar_t__ etype; int /*<<< orphan*/ * salt; int /*<<< orphan*/  s2kparams; } ;
typedef  TYPE_7__ ETYPE_INFO2 ;
typedef  TYPE_8__ AS_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_PW_SALT ; 
 scalar_t__ decode_ETYPE_INFO2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,size_t*) ; 
 int /*<<< orphan*/  free_ETYPE_INFO2 (TYPE_7__*) ; 
 int /*<<< orphan*/  krb5_free_salt (int /*<<< orphan*/ ,TYPE_5__) ; 
 scalar_t__ krb5_get_pw_salt (int /*<<< orphan*/ ,int /*<<< orphan*/  const,TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ set_paid (struct pa_info_data*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pa_info_data *
pa_etype_info2(krb5_context context,
	       const krb5_principal client,
	       const AS_REQ *asreq,
	       struct pa_info_data *paid,
	       heim_octet_string *data)
{
    krb5_error_code ret;
    ETYPE_INFO2 e;
    size_t sz;
    size_t i, j;

    memset(&e, 0, sizeof(e));
    ret = decode_ETYPE_INFO2(data->data, data->length, &e, &sz);
    if (ret)
	goto out;
    if (e.len == 0)
	goto out;
    for (j = 0; j < asreq->req_body.etype.len; j++) {
	for (i = 0; i < e.len; i++) {
	    if (asreq->req_body.etype.val[j] == e.val[i].etype) {
		krb5_salt salt;
		if (e.val[i].salt == NULL)
		    ret = krb5_get_pw_salt(context, client, &salt);
		else {
		    salt.saltvalue.data = *e.val[i].salt;
		    salt.saltvalue.length = strlen(*e.val[i].salt);
		    ret = 0;
		}
		if (ret == 0)
		    ret = set_paid(paid, context, e.val[i].etype,
				   KRB5_PW_SALT,
				   salt.saltvalue.data,
				   salt.saltvalue.length,
				   e.val[i].s2kparams);
		if (e.val[i].salt == NULL)
		    krb5_free_salt(context, salt);
		if (ret == 0) {
		    free_ETYPE_INFO2(&e);
		    return paid;
		}
	    }
	}
    }
 out:
    free_ETYPE_INFO2(&e);
    return NULL;
}