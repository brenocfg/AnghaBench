#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* provider_p ;
typedef  int /*<<< orphan*/  profile_p ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  const* bdaddr_p ;
struct TYPE_6__ {int handle; int /*<<< orphan*/  fd; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/ * data; int /*<<< orphan*/  profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  change_state ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int handle ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int) ; 
 int /*<<< orphan*/  provider_next ; 
 int /*<<< orphan*/  providers ; 

provider_p
provider_register(profile_p const profile, bdaddr_p const bdaddr, int32_t fd,
	uint8_t const *data, uint32_t datalen)
{
	provider_p	provider = calloc(1, sizeof(*provider));

	if (provider != NULL) {
		provider->data = malloc(datalen);
		if (provider->data != NULL) {
			provider->profile = profile;
			memcpy(provider->data, data, datalen);

			/*
			 * Record handles 0x0 and 0x1 are reserved
			 * for SDP itself
			 */

			if (++ handle <= 1)
				handle = 2;

			provider->handle = handle;

			memcpy(&provider->bdaddr, bdaddr,
				sizeof(provider->bdaddr));
			provider->fd = fd;

			TAILQ_INSERT_TAIL(&providers, provider, provider_next);
			change_state ++;
		} else {
			free(provider);
			provider = NULL;
		}
	}

	return (provider);
}