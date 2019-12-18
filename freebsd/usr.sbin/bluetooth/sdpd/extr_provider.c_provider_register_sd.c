#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* provider_p ;
typedef  int /*<<< orphan*/  profile_t ;
typedef  int int32_t ;
struct TYPE_7__ {int handle; int fd; int /*<<< orphan*/ * profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  change_state ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  provider_next ; 
 int /*<<< orphan*/  providers ; 

int32_t
provider_register_sd(int32_t fd)
{
	extern profile_t	sd_profile_descriptor;
	extern profile_t	bgd_profile_descriptor;

	provider_p		sd = calloc(1, sizeof(*sd));
	provider_p		bgd = calloc(1, sizeof(*bgd));

	if (sd == NULL || bgd == NULL) {
		if (sd != NULL)
			free(sd);

		if (bgd != NULL)
			free(bgd);

		return (-1);
	}

	sd->profile = &sd_profile_descriptor;
	bgd->handle = 0;
	sd->fd = fd;
	TAILQ_INSERT_HEAD(&providers, sd, provider_next);

	bgd->profile = &bgd_profile_descriptor;
	bgd->handle = 1;
	sd->fd = fd;
	TAILQ_INSERT_AFTER(&providers, sd, bgd, provider_next);
	
	change_state ++;

	return (0);
}