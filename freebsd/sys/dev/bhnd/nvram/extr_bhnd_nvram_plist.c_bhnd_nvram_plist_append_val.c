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
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 int ENOMEM ; 
 int bhnd_nvram_plist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_nvram_prop_new (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_prop_release (int /*<<< orphan*/ *) ; 

int
bhnd_nvram_plist_append_val(bhnd_nvram_plist *plist, const char *name,
    bhnd_nvram_val *val)
{
	bhnd_nvram_prop	*prop;
	int		 error;

	if ((prop = bhnd_nvram_prop_new(name, val)) == NULL)
		return (ENOMEM);

	error = bhnd_nvram_plist_append(plist, prop);
	bhnd_nvram_prop_release(prop);

	return (error);
}