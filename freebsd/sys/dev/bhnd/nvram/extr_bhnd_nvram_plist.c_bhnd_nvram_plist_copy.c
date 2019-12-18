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
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int ENOMEM ; 
 int bhnd_nvram_plist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_new () ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_plist_release (int /*<<< orphan*/ *) ; 

bhnd_nvram_plist *
bhnd_nvram_plist_copy(bhnd_nvram_plist *plist)
{
	bhnd_nvram_plist	*copy;
	bhnd_nvram_prop		*prop;
	int			 error;

	/* Allocate new, empty plist */
	if ((copy = bhnd_nvram_plist_new()) == NULL)
		return (NULL);

	/* Append all properties */
	prop = NULL;
	while ((prop = bhnd_nvram_plist_next(plist, prop)) != NULL) {
		error = bhnd_nvram_plist_append(copy, prop);
		if (error) {
			if (error != ENOMEM) {
				BHND_NV_LOG("error copying property: %d\n",
				    error);
			}

			bhnd_nvram_plist_release(copy);
			return (NULL);
		}
	}

	/* Return ownership of the copy to our caller */
	return (copy);
}