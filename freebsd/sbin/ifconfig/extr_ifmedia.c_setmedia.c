#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifmediareq {int ifm_current; int /*<<< orphan*/ * ifm_ulist; } ;
struct afswtch {int dummy; } ;
struct TYPE_2__ {int ifr_media; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int IFM_IMASK ; 
 int IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callback_register (int /*<<< orphan*/ ,void*) ; 
 int get_media_subtype (int,char const*) ; 
 struct ifmediareq* ifmedia_getstate (int) ; 
 TYPE_1__ ifr ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  setifmediacallback ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setmedia(const char *val, int d, int s, const struct afswtch *afp)
{
	struct ifmediareq *ifmr;
	int subtype;

	ifmr = ifmedia_getstate(s);

	/*
	 * We are primarily concerned with the top-level type.
	 * However, "current" may be only IFM_NONE, so we just look
	 * for the top-level type in the first "supported type"
	 * entry.
	 *
	 * (I'm assuming that all supported media types for a given
	 * interface will be the same top-level type..)
	 */
	subtype = get_media_subtype(IFM_TYPE(ifmr->ifm_ulist[0]), val);

	strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	ifr.ifr_media = (ifmr->ifm_current & IFM_IMASK) |
	    IFM_TYPE(ifmr->ifm_ulist[0]) | subtype;

	ifmr->ifm_current = ifr.ifr_media;
	callback_register(setifmediacallback, (void *)ifmr);
}