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
struct keys {void** keys_values; int /*<<< orphan*/ ** keys_names; } ;

/* Variables and functions */
 int KEYS_MAX ; 
 void* checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_debugx (char*,char const*,char const*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 

void
keys_add(struct keys *keys, const char *name, const char *value)
{
	int i;

	log_debugx("key to send: \"%s=%s\"", name, value);

	/*
	 * Note that we don't check for duplicates here, as they are perfectly
	 * fine in responses, e.g. the "TargetName" keys in discovery sesion
	 * response.
	 */
	for (i = 0; i < KEYS_MAX; i++) {
		if (keys->keys_names[i] == NULL) {
			keys->keys_names[i] = checked_strdup(name);
			keys->keys_values[i] = checked_strdup(value);
			return;
		}
	}
	log_errx(1, "too many keys");
}