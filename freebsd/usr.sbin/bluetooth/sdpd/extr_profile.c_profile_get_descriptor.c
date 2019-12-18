#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  profiles ;
struct TYPE_4__ {scalar_t__ uuid; } ;
typedef  TYPE_1__ profile_t ;
typedef  TYPE_1__* profile_p ;
typedef  int int32_t ;

/* Variables and functions */

profile_p
profile_get_descriptor(uint16_t uuid)
{
  	extern	profile_t	audio_sink_profile_descriptor;
	extern	profile_t	audio_source_profile_descriptor;
	extern	profile_t	dun_profile_descriptor;
	extern	profile_t	ftrn_profile_descriptor;
	extern	profile_t	irmc_profile_descriptor;
	extern	profile_t	irmc_command_profile_descriptor;
	extern	profile_t	lan_profile_descriptor;
	extern	profile_t	opush_profile_descriptor;
	extern	profile_t	sp_profile_descriptor;
	extern	profile_t	nap_profile_descriptor;
	extern	profile_t	gn_profile_descriptor;
	extern	profile_t	panu_profile_descriptor;

	static const profile_p	profiles[] = {
		&audio_sink_profile_descriptor,
		&audio_source_profile_descriptor,
		&dun_profile_descriptor,
		&ftrn_profile_descriptor,
		&irmc_profile_descriptor,
		&irmc_command_profile_descriptor,
		&lan_profile_descriptor,
		&opush_profile_descriptor,
		&sp_profile_descriptor,
		&nap_profile_descriptor,
		&gn_profile_descriptor,
		&panu_profile_descriptor
	};

	int32_t			i;

	for (i = 0; i < sizeof(profiles)/sizeof(profiles[0]); i++)
		if (profiles[i]->uuid == uuid)
			return (profiles[i]);

	return (NULL);
}