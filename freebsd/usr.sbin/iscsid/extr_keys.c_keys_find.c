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
struct keys {char const** keys_values; int /*<<< orphan*/ ** keys_names; } ;

/* Variables and functions */
 int KEYS_MAX ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

const char *
keys_find(struct keys *keys, const char *name)
{
	int i;

	/*
	 * Note that we don't handle duplicated key names here,
	 * as they are not supposed to happen in requests, and if they do,
	 * it's an initiator error.
	 */
	for (i = 0; i < KEYS_MAX; i++) {
		if (keys->keys_names[i] == NULL)
			return (NULL);
		if (strcmp(keys->keys_names[i], name) == 0)
			return (keys->keys_values[i]);
	}
	return (NULL);
}