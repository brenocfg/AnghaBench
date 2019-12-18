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
typedef  size_t u_int ;
struct bhnd_core_match {int dummy; } ;
struct bhnd_core_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ bhnd_core_matches (struct bhnd_core_info const*,struct bhnd_core_match const*) ; 

const struct bhnd_core_info *
bhnd_match_core(const struct bhnd_core_info *cores, u_int num_cores,
    const struct bhnd_core_match *desc)
{
	for (u_int i = 0; i < num_cores; i++) {
		if (bhnd_core_matches(&cores[i], desc))
			return &cores[i];
	}

	return (NULL);
}