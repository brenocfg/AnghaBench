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
struct bhnd_nvram_data {int dummy; } ;
struct bhnd_nvram_bcmraw {char* data; } ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *
bhnd_nvram_bcmraw_next(struct bhnd_nvram_data *nv, void **cookiep)
{
	struct bhnd_nvram_bcmraw	*bcm;
	const char			*envp;

	bcm = (struct bhnd_nvram_bcmraw *)nv;

	if (*cookiep == NULL) {
		/* Start at the first NVRAM data record */
		envp = bcm->data;
	} else {
		/* Seek to next record */
		envp = *cookiep;
		envp += strlen(envp) + 1;	/* key + '\0' */
		envp += strlen(envp) + 1;	/* value + '\0' */
	}

	/* EOF? */
	if (*envp == '\0')
		return (NULL);

	*cookiep = (void *)(uintptr_t)envp;
	return (envp);
}