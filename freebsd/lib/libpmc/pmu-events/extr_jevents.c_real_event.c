#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* event; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* fixed ; 
 int /*<<< orphan*/  strcasecmp (char const*,scalar_t__) ; 

__attribute__((used)) static const char *real_event(const char *name, char *event)
{
	int i;

	if (!name)
		return NULL;

	for (i = 0; fixed[i].name; i++)
		if (!strcasecmp(name, fixed[i].name))
			return fixed[i].event;
	return event;
}