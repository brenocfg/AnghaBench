#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct krb5_krbhst_data {int flags; scalar_t__ (* get_next ) (TYPE_2__*,struct krb5_krbhst_data*,TYPE_1__**) ;int /*<<< orphan*/  realm; int /*<<< orphan*/  def_port; int /*<<< orphan*/  port; } ;
struct TYPE_14__ {int /*<<< orphan*/  proto; } ;
typedef  TYPE_1__ krb5_krbhst_info ;
typedef  scalar_t__ krb5_error_code ;
typedef  TYPE_2__* krb5_context ;
struct TYPE_15__ {scalar_t__ srv_lookup; } ;

/* Variables and functions */
 int KD_CONFIG ; 
 int KD_CONFIG_EXISTS ; 
 int KD_PLUGIN ; 
 int KD_SRV_TCP ; 
 int KD_SRV_UDP ; 
 scalar_t__ KRB5_KDC_UNREACH ; 
 int /*<<< orphan*/  _krb5_debug (TYPE_2__*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ admin_get_next (TYPE_2__*,struct krb5_krbhst_data*,TYPE_1__**) ; 
 int /*<<< orphan*/  config_get_hosts (TYPE_2__*,struct krb5_krbhst_data*,char*) ; 
 scalar_t__ get_next (struct krb5_krbhst_data*,TYPE_1__**) ; 
 scalar_t__ krbhst_empty (struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  krbhst_get_default_proto (struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  locate_service_kpasswd ; 
 int /*<<< orphan*/  plugin_get_hosts (TYPE_2__*,struct krb5_krbhst_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srv_get_hosts (TYPE_2__*,struct krb5_krbhst_data*,char*,char*) ; 
 scalar_t__ stub1 (TYPE_2__*,struct krb5_krbhst_data*,TYPE_1__**) ; 

__attribute__((used)) static krb5_error_code
kpasswd_get_next(krb5_context context,
		 struct krb5_krbhst_data *kd,
		 krb5_krbhst_info **host)
{
    krb5_error_code ret;

    if ((kd->flags & KD_PLUGIN) == 0) {
	plugin_get_hosts(context, kd, locate_service_kpasswd);
	kd->flags |= KD_PLUGIN;
	if(get_next(kd, host))
	    return 0;
    }

    if((kd->flags & KD_CONFIG) == 0) {
	config_get_hosts(context, kd, "kpasswd_server");
	kd->flags |= KD_CONFIG;
	if(get_next(kd, host))
	    return 0;
    }

    if (kd->flags & KD_CONFIG_EXISTS) {
	_krb5_debug(context, 1,
		    "Configuration exists for realm %s, wont go to DNS",
		    kd->realm);
	return KRB5_KDC_UNREACH;
    }

    if(context->srv_lookup) {
	if((kd->flags & KD_SRV_UDP) == 0) {
	    srv_get_hosts(context, kd, "udp", "kpasswd");
	    kd->flags |= KD_SRV_UDP;
	    if(get_next(kd, host))
		return 0;
	}
	if((kd->flags & KD_SRV_TCP) == 0) {
	    srv_get_hosts(context, kd, "tcp", "kpasswd");
	    kd->flags |= KD_SRV_TCP;
	    if(get_next(kd, host))
		return 0;
	}
    }

    /* no matches -> try admin */

    if (krbhst_empty(kd)) {
	kd->flags = 0;
	kd->port  = kd->def_port;
	kd->get_next = admin_get_next;
	ret = (*kd->get_next)(context, kd, host);
	if (ret == 0)
	    (*host)->proto = krbhst_get_default_proto(kd);
	return ret;
    }

    _krb5_debug(context, 0, "No kpasswd entries found for realm %s", kd->realm);

    return KRB5_KDC_UNREACH;
}