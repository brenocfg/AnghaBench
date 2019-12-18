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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  append_string (char*) ; 
 int /*<<< orphan*/  finish_packet () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  start_packet () ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
check_features(const uint8_t *data, size_t len)
{
	char *feature, *next_feature, *str, *value;
	bool supported;

	str = malloc(len + 1);
	memcpy(str, data, len);
	str[len] = '\0';
	next_feature = str;

	while ((feature = strsep(&next_feature, ";")) != NULL) {
		/*
		 * Null features shouldn't exist, but skip if they
		 * do.
		 */
		if (strcmp(feature, "") == 0)
			continue;

		/*
		 * Look for the value or supported / not supported
		 * flag.
		 */
		value = strchr(feature, '=');
		if (value != NULL) {
			*value = '\0';
			value++;
			supported = true;
		} else {
			value = feature + strlen(feature) - 1;
			switch (*value) {
			case '+':
				supported = true;
				break;
			case '-':
				supported = false;
				break;
			default:
				/*
				 * This is really a protocol error,
				 * but we just ignore malformed
				 * features for ease of
				 * implementation.
				 */
				continue;
			}
			value = NULL;
		}

		/* No currently supported features. */
	}
	free(str);

	start_packet();

	/* This is an arbitrary limit. */
	append_string("PacketSize=4096");
	finish_packet();
}