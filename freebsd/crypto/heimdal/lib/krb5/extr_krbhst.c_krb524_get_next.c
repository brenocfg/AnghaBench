#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct krb5_krbhst_data {int flags; int /*<<< orphan*/  realm; int /*<<< orphan*/  (* get_next ) (TYPE_1__*,struct krb5_krbhst_data*,int /*<<< orphan*/ **) ;int /*<<< orphan*/  def_port; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  krb5_krbhst_info ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_1__* krb5_context ;
struct TYPE_9__ {scalar_t__ srv_lookup; } ;

/* Variables and functions */
 int KD_CONFIG ; 
 int KD_CONFIG_EXISTS ; 
 int KD_PLUGIN ; 
 int KD_SRV_TCP ; 
 int KD_SRV_UDP ; 
 int /*<<< orphan*/  KRB5_KDC_UNREACH ; 
 int /*<<< orphan*/  _krb5_debug (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_get_hosts (TYPE_1__*,struct krb5_krbhst_data*,char*) ; 
 scalar_t__ get_next (struct krb5_krbhst_data*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kdc_get_next (TYPE_1__*,struct krb5_krbhst_data*,int /*<<< orphan*/ **) ; 
 scalar_t__ krbhst_empty (struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  locate_service_krb524 ; 
 int /*<<< orphan*/  plugin_get_hosts (TYPE_1__*,struct krb5_krbhst_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srv_get_hosts (TYPE_1__*,struct krb5_krbhst_data*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct krb5_krbhst_data*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static krb5_error_code
krb524_get_next(krb5_context context,
		struct krb5_krbhst_data *kd,
		krb5_krbhst_info **host)
{
    if ((kd->flags & KD_PLUGIN) == 0) {
	plugin_get_hosts(context, kd, locate_service_krb524);
	kd->flags |= KD_PLUGIN;
	if(get_next(kd, host))
	    return 0;
    }

    if((kd->flags & KD_CONFIG) == 0) {
	config_get_hosts(context, kd, "krb524_server");
	if(get_next(kd, host))
	    return 0;
	kd->flags |= KD_CONFIG;
    }

    if (kd->flags & KD_CONFIG_EXISTS) {
	_krb5_debug(context, 1,
		    "Configuration exists for realm %s, wont go to DNS",
		    kd->realm);
	return KRB5_KDC_UNREACH;
    }

    if(context->srv_lookup) {
	if((kd->flags & KD_SRV_UDP) == 0) {
	    srv_get_hosts(context, kd, "udp", "krb524");
	    kd->flags |= KD_SRV_UDP;
	    if(get_next(kd, host))
		return 0;
	}

	if((kd->flags & KD_SRV_TCP) == 0) {
	    srv_get_hosts(context, kd, "tcp", "krb524");
	    kd->flags |= KD_SRV_TCP;
	    if(get_next(kd, host))
		return 0;
	}
    }

    /* no matches -> try kdc */

    if (krbhst_empty(kd)) {
	kd->flags = 0;
	kd->port  = kd->def_port;
	kd->get_next = kdc_get_next;
	return (*kd->get_next)(context, kd, host);
    }

    _krb5_debug(context, 0, "No kpasswd entries found for realm %s", kd->realm);

    return KRB5_KDC_UNREACH;
}