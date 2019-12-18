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
struct fire_desc {int /*<<< orphan*/ * fd_string; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct fire_desc* fire_compats ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const struct fire_desc *
fire_get_desc(device_t dev)
{
	const struct fire_desc *desc;
	const char *compat;

	compat = ofw_bus_get_compat(dev);
	if (compat == NULL)
		return (NULL);
	for (desc = fire_compats; desc->fd_string != NULL; desc++)
		if (strcmp(desc->fd_string, compat) == 0)
			return (desc);
	return (NULL);
}