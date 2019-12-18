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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_get_prop (int /*<<< orphan*/ *,char const*) ; 
 int bhnd_nvram_prop_encode (int /*<<< orphan*/ *,void*,size_t*,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_plist_get_encoded(bhnd_nvram_plist *plist, const char *name,
    void *outp, size_t olen, bhnd_nvram_type otype)
{
	bhnd_nvram_prop *prop;

	if ((prop = bhnd_nvram_plist_get_prop(plist, name)) == NULL)
		return (ENOENT);

	return (bhnd_nvram_prop_encode(prop, outp, &olen, otype));
}