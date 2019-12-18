#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_15__ {int /*<<< orphan*/  allow_anonymous; } ;
typedef  TYPE_2__ krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_3__* krb5_context ;
struct TYPE_14__ {int invalid; int forwardable; int forwarded; int proxiable; int proxy; int may_postdate; int postdated; int renewable; } ;
struct TYPE_19__ {scalar_t__* starttime; scalar_t__ endtime; scalar_t__ authtime; int /*<<< orphan*/ * renew_till; TYPE_1__ flags; int /*<<< orphan*/  caddr; } ;
struct TYPE_18__ {scalar_t__ request_anonymous; scalar_t__ renew; scalar_t__ renewable; scalar_t__ postdated; scalar_t__ allow_postdate; scalar_t__ proxy; scalar_t__ proxiable; scalar_t__ forwarded; scalar_t__ forwardable; scalar_t__ validate; } ;
struct TYPE_17__ {scalar_t__* from; int /*<<< orphan*/ * rtime; int /*<<< orphan*/  addresses; TYPE_5__ kdc_options; } ;
struct TYPE_16__ {scalar_t__ max_skew; } ;
typedef  TYPE_4__ KDC_REQ_BODY ;
typedef  TYPE_5__ KDCOptions ;
typedef  TYPE_6__ EncTicketPart ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KRB5KDC_ERR_BADOPTION ; 
 int /*<<< orphan*/  KRB5KDC_ERR_CANNOT_POSTDATE ; 
 int /*<<< orphan*/  KRB5KRB_AP_ERR_TKT_INVALID ; 
 int /*<<< orphan*/  KRB5KRB_AP_ERR_TKT_NYV ; 
 int /*<<< orphan*/  _kdc_fix_time (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kdc_log (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kdc_time ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static krb5_error_code
check_tgs_flags(krb5_context context,
		krb5_kdc_configuration *config,
		KDC_REQ_BODY *b, const EncTicketPart *tgt, EncTicketPart *et)
{
    KDCOptions f = b->kdc_options;

    if(f.validate){
	if(!tgt->flags.invalid || tgt->starttime == NULL){
	    kdc_log(context, config, 0,
		    "Bad request to validate ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	if(*tgt->starttime > kdc_time){
	    kdc_log(context, config, 0,
		    "Early request to validate ticket");
	    return KRB5KRB_AP_ERR_TKT_NYV;
	}
	/* XXX  tkt = tgt */
	et->flags.invalid = 0;
    }else if(tgt->flags.invalid){
	kdc_log(context, config, 0,
		"Ticket-granting ticket has INVALID flag set");
	return KRB5KRB_AP_ERR_TKT_INVALID;
    }

    if(f.forwardable){
	if(!tgt->flags.forwardable){
	    kdc_log(context, config, 0,
		    "Bad request for forwardable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	et->flags.forwardable = 1;
    }
    if(f.forwarded){
	if(!tgt->flags.forwardable){
	    kdc_log(context, config, 0,
		    "Request to forward non-forwardable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	et->flags.forwarded = 1;
	et->caddr = b->addresses;
    }
    if(tgt->flags.forwarded)
	et->flags.forwarded = 1;

    if(f.proxiable){
	if(!tgt->flags.proxiable){
	    kdc_log(context, config, 0,
		    "Bad request for proxiable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	et->flags.proxiable = 1;
    }
    if(f.proxy){
	if(!tgt->flags.proxiable){
	    kdc_log(context, config, 0,
		    "Request to proxy non-proxiable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	et->flags.proxy = 1;
	et->caddr = b->addresses;
    }
    if(tgt->flags.proxy)
	et->flags.proxy = 1;

    if(f.allow_postdate){
	if(!tgt->flags.may_postdate){
	    kdc_log(context, config, 0,
		    "Bad request for post-datable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	et->flags.may_postdate = 1;
    }
    if(f.postdated){
	if(!tgt->flags.may_postdate){
	    kdc_log(context, config, 0,
		    "Bad request for postdated ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	if(b->from)
	    *et->starttime = *b->from;
	et->flags.postdated = 1;
	et->flags.invalid = 1;
    }else if(b->from && *b->from > kdc_time + context->max_skew){
	kdc_log(context, config, 0, "Ticket cannot be postdated");
	return KRB5KDC_ERR_CANNOT_POSTDATE;
    }

    if(f.renewable){
	if(!tgt->flags.renewable || tgt->renew_till == NULL){
	    kdc_log(context, config, 0,
		    "Bad request for renewable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	et->flags.renewable = 1;
	ALLOC(et->renew_till);
	_kdc_fix_time(&b->rtime);
	*et->renew_till = *b->rtime;
    }
    if(f.renew){
	time_t old_life;
	if(!tgt->flags.renewable || tgt->renew_till == NULL){
	    kdc_log(context, config, 0,
		    "Request to renew non-renewable ticket");
	    return KRB5KDC_ERR_BADOPTION;
	}
	old_life = tgt->endtime;
	if(tgt->starttime)
	    old_life -= *tgt->starttime;
	else
	    old_life -= tgt->authtime;
	et->endtime = *et->starttime + old_life;
	if (et->renew_till != NULL)
	    et->endtime = min(*et->renew_till, et->endtime);
    }

#if 0
    /* checks for excess flags */
    if(f.request_anonymous && !config->allow_anonymous){
	kdc_log(context, config, 0,
		"Request for anonymous ticket");
	return KRB5KDC_ERR_BADOPTION;
    }
#endif
    return 0;
}