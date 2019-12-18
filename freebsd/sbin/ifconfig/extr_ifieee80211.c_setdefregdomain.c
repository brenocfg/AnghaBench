#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regdomain {scalar_t__ sku; int /*<<< orphan*/ * cc; } ;
struct regdata {int dummy; } ;
struct TYPE_3__ {scalar_t__ regdomain; scalar_t__ country; scalar_t__* isocc; } ;

/* Variables and functions */
 scalar_t__ CTRY_DEFAULT ; 
 int /*<<< orphan*/  SKU_FCC ; 
 int /*<<< orphan*/  defaultcountry (struct regdomain const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct regdata* getregdata () ; 
 int /*<<< orphan*/  getregdomain (int) ; 
 struct regdomain* lib80211_regdomain_findbysku (struct regdata*,int /*<<< orphan*/ ) ; 
 TYPE_1__ regdomain ; 
 int /*<<< orphan*/  setregdomain_cb (int,TYPE_1__*) ; 

__attribute__((used)) static void
setdefregdomain(int s)
{
	struct regdata *rdp = getregdata();
	const struct regdomain *rd;

	/* Check if regdomain/country was already set by a previous call. */
	/* XXX is it possible? */
	if (regdomain.regdomain != 0 ||
	    regdomain.country != CTRY_DEFAULT)
		return;

	getregdomain(s);

	/* Check if it was already set by the driver. */
	if (regdomain.regdomain != 0 ||
	    regdomain.country != CTRY_DEFAULT)
		return;

	/* Set FCC/US as default. */
	rd = lib80211_regdomain_findbysku(rdp, SKU_FCC);
	if (rd == NULL)
		errx(1, "FCC regdomain was not found");

	regdomain.regdomain = rd->sku;
	if (rd->cc != NULL)
		defaultcountry(rd);

	/* Send changes to net80211. */
	setregdomain_cb(s, &regdomain);

	/* Cleanup (so it can be overriden by subsequent parameters). */
	regdomain.regdomain = 0;
	regdomain.country = CTRY_DEFAULT;
	regdomain.isocc[0] = 0;
	regdomain.isocc[1] = 0;
}