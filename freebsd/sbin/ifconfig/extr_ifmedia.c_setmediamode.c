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
 int IFM_MMASK ; 
 int /*<<< orphan*/  IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callback_register (int /*<<< orphan*/ ,void*) ; 
 int get_media_mode (int /*<<< orphan*/ ,char const*) ; 
 struct ifmediareq* ifmedia_getstate (int) ; 
 TYPE_1__ ifr ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  setifmediacallback ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setmediamode(const char *val, int d, int s, const struct afswtch *afp)
{
	struct ifmediareq *ifmr;
	int mode;

	ifmr = ifmedia_getstate(s);

	mode = get_media_mode(IFM_TYPE(ifmr->ifm_ulist[0]), val);

	strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	ifr.ifr_media = (ifmr->ifm_current & ~IFM_MMASK) | mode;

	ifmr->ifm_current = ifr.ifr_media;
	callback_register(setifmediacallback, (void *)ifmr);
}