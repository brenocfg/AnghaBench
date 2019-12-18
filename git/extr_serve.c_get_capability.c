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
struct protocol_capability {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct protocol_capability*) ; 
 struct protocol_capability* capabilities ; 
 scalar_t__ skip_prefix (char const*,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static struct protocol_capability *get_capability(const char *key)
{
	int i;

	if (!key)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(capabilities); i++) {
		struct protocol_capability *c = &capabilities[i];
		const char *out;
		if (skip_prefix(key, c->name, &out) && (!*out || *out == '='))
			return c;
	}

	return NULL;
}