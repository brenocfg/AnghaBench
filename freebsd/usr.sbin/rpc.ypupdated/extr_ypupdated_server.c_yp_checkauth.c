#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int oa_flavor; } ;
struct svc_req {scalar_t__ rq_clntcred; TYPE_1__ rq_cred; } ;
struct TYPE_4__ {int /*<<< orphan*/  window; } ;
struct authdes_cred {TYPE_2__ adc_fullname; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;

/* Variables and functions */
 int AUTH_BADCRED ; 
#define  AUTH_DES 130 
#define  AUTH_NONE 129 
 int AUTH_OK ; 
 int AUTH_REJECTEDCRED ; 
 int AUTH_TOOWEAK ; 
#define  AUTH_UNIX 128 
 int /*<<< orphan*/  WINDOW ; 
 int /*<<< orphan*/  yp_error (char*) ; 

__attribute__((used)) static enum auth_stat
yp_checkauth(struct svc_req *svcreq)
{
	struct authdes_cred *des_cred;

	switch (svcreq->rq_cred.oa_flavor) {
	case AUTH_DES:
		des_cred = (struct authdes_cred *) svcreq->rq_clntcred;
		if (des_cred->adc_fullname.window > WINDOW) {
			yp_error("warning: client-specified window size \
was too large -- possible spoof attempt");
			return(AUTH_BADCRED);
		}
		return(AUTH_OK);
		break;
	case AUTH_UNIX:
	case AUTH_NONE:
		yp_error("warning: client didn't use DES authentication");
		return(AUTH_TOOWEAK);
		break;
	default:
		yp_error("client used unknown auth flavor");
		return(AUTH_REJECTEDCRED);
		break;
	}
}