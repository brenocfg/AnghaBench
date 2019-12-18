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
 int bhnd_nvram_plist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
bhnd_nvram_plist_append_list(bhnd_nvram_plist *plist, bhnd_nvram_plist *tail)
{
	bhnd_nvram_prop	*p;
	int		 error;

	p = NULL;
	while ((p = bhnd_nvram_plist_next(tail, p)) != NULL) {
		if ((error = bhnd_nvram_plist_append(plist, p)))
			return (error);
	}

	return (0);
}