#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct descr {scalar_t__ type; int /*<<< orphan*/  addr_string; int /*<<< orphan*/  sa; } ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_7__ {scalar_t__ length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;

/* Variables and functions */
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 scalar_t__ krb5_kdc_process_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,size_t,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  krb5_kdc_save_request (int /*<<< orphan*/ ,scalar_t__,void*,size_t,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_kdc_update_time (int /*<<< orphan*/ *) ; 
 scalar_t__ request_log ; 
 int /*<<< orphan*/  send_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct descr*,TYPE_1__*) ; 

__attribute__((used)) static void
do_request(krb5_context context,
	   krb5_kdc_configuration *config,
	   void *buf, size_t len, krb5_boolean prependlength,
	   struct descr *d)
{
    krb5_error_code ret;
    krb5_data reply;
    int datagram_reply = (d->type == SOCK_DGRAM);

    krb5_kdc_update_time(NULL);

    krb5_data_zero(&reply);
    ret = krb5_kdc_process_request(context, config,
				   buf, len, &reply, &prependlength,
				   d->addr_string, d->sa,
				   datagram_reply);
    if(request_log)
	krb5_kdc_save_request(context, request_log, buf, len, &reply, d->sa);
    if(reply.length){
	send_reply(context, config, prependlength, d, &reply);
	krb5_data_free(&reply);
    }
    if(ret)
	kdc_log(context, config, 0,
		"Failed processing %lu byte request from %s",
		(unsigned long)len, d->addr_string);
}