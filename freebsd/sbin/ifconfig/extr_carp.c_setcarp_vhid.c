#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct in_aliasreq {scalar_t__ ifra_vhid; } ;
struct in6_aliasreq {scalar_t__ ifra_vhid; } ;
struct afswtch {int af_af; scalar_t__ af_name; scalar_t__ af_addreq; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ CARP_MAXVHID ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  callback_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ carpr_vhid ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  setcarp_callback ; 

__attribute__((used)) static void
setcarp_vhid(const char *val, int d, int s, const struct afswtch *afp)
{

	carpr_vhid = atoi(val);

	if (carpr_vhid <= 0 || carpr_vhid > CARP_MAXVHID)
		errx(1, "vhid must be greater than 0 and less than %u",
		    CARP_MAXVHID);

	switch (afp->af_af) {
#ifdef INET
	case AF_INET:
	    {
		struct in_aliasreq *ifra;

		ifra = (struct in_aliasreq *)afp->af_addreq;
		ifra->ifra_vhid = carpr_vhid;
		break;
	    }
#endif
#ifdef INET6
	case AF_INET6:
	    {
		struct in6_aliasreq *ifra;

		ifra = (struct in6_aliasreq *)afp->af_addreq;
		ifra->ifra_vhid = carpr_vhid;
		break;
	    }
#endif
	default:
		errx(1, "%s doesn't support carp(4)", afp->af_name);
	}

	callback_register(setcarp_callback, NULL);
}