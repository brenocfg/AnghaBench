#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  KDC_REQ ;

/* Variables and functions */
 scalar_t__ _kdc_as_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,char const*,struct sockaddr*,int) ; 
 scalar_t__ decode_AS_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_AS_REQ (int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
kdc_as_req(krb5_context context,
	   krb5_kdc_configuration *config,
	   krb5_data *req_buffer,
	   krb5_data *reply,
	   const char *from,
	   struct sockaddr *addr,
	   int datagram_reply,
	   int *claim)
{
    krb5_error_code ret;
    KDC_REQ req;
    size_t len;

    ret = decode_AS_REQ(req_buffer->data, req_buffer->length, &req, &len);
    if (ret)
	return ret;

    *claim = 1;

    ret = _kdc_as_rep(context, config, &req, req_buffer,
		      reply, from, addr, datagram_reply);
    free_AS_REQ(&req);
    return ret;
}