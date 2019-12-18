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
struct videomode {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int videomode_count ; 
 struct videomode const* videomode_list ; 

__attribute__((used)) static const struct videomode *
edid_mode_lookup_list(const char *name)
{
	int	i;

	for (i = 0; i < videomode_count; i++)
		if (strcmp(name, videomode_list[i].name) == 0)
			return &videomode_list[i];
	return NULL;
}