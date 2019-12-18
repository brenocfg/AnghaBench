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
typedef  scalar_t__ uint32_t ;
struct pccard_product {scalar_t__ pp_vendor; scalar_t__ pp_product; int /*<<< orphan*/ ** pp_cis; scalar_t__ pp_name; } ;
typedef  int (* pccard_product_match_fn ) (int /*<<< orphan*/ ,struct pccard_product const*,int) ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCCARD_PRODUCT_ANY ; 
 scalar_t__ PCCARD_VENDOR_ANY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pccard_get_cis3_str (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ pccard_get_cis4_str (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ pccard_get_product (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ pccard_get_product_str (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ pccard_get_vendor (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ pccard_get_vendor_str (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int stub1 (int /*<<< orphan*/ ,struct pccard_product const*,int) ; 

__attribute__((used)) static const struct pccard_product *
pccard_do_product_lookup(device_t bus, device_t dev,
    const struct pccard_product *tab, size_t ent_size,
    pccard_product_match_fn matchfn)
{
	const struct pccard_product *ent;
	int matches;
	uint32_t vendor;
	uint32_t prod;
	const char *vendorstr;
	const char *prodstr;
	const char *cis3str;
	const char *cis4str;

#ifdef DIAGNOSTIC
	if (sizeof *ent > ent_size)
		panic("pccard_product_lookup: bogus ent_size %jd",
		    (intmax_t) ent_size);
#endif
	if (pccard_get_vendor(dev, &vendor))
		return (NULL);
	if (pccard_get_product(dev, &prod))
		return (NULL);
	if (pccard_get_vendor_str(dev, &vendorstr))
		return (NULL);
	if (pccard_get_product_str(dev, &prodstr))
		return (NULL);
	if (pccard_get_cis3_str(dev, &cis3str))
		return (NULL);
	if (pccard_get_cis4_str(dev, &cis4str))
		return (NULL);
	for (ent = tab; ent->pp_vendor != 0; ent =
	    (const struct pccard_product *) ((const char *) ent + ent_size)) {
		matches = 1;
		if (ent->pp_vendor == PCCARD_VENDOR_ANY &&
		    ent->pp_product == PCCARD_PRODUCT_ANY &&
		    ent->pp_cis[0] == NULL &&
		    ent->pp_cis[1] == NULL) {
			if (ent->pp_name)
				device_printf(dev,
				    "Total wildcard entry ignored for %s\n",
				    ent->pp_name);
			continue;
		}
		if (matches && ent->pp_vendor != PCCARD_VENDOR_ANY &&
		    vendor != ent->pp_vendor)
			matches = 0;
		if (matches && ent->pp_product != PCCARD_PRODUCT_ANY &&
		    prod != ent->pp_product)
			matches = 0;
		if (matches && ent->pp_cis[0] &&
		    (vendorstr == NULL ||
		    strcmp(ent->pp_cis[0], vendorstr) != 0))
			matches = 0;
		if (matches && ent->pp_cis[1] &&
		    (prodstr == NULL ||
		    strcmp(ent->pp_cis[1], prodstr) != 0))
			matches = 0;
		if (matches && ent->pp_cis[2] &&
		    (cis3str == NULL ||
		    strcmp(ent->pp_cis[2], cis3str) != 0))
			matches = 0;
		if (matches && ent->pp_cis[3] &&
		    (cis4str == NULL ||
		    strcmp(ent->pp_cis[3], cis4str) != 0))
			matches = 0;
		if (matchfn != NULL)
			matches = (*matchfn)(dev, ent, matches);
		if (matches)
			return (ent);
	}
	return (NULL);
}