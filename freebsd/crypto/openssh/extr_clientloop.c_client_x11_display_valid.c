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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_X11_VALID_DISPLAY_CHARS ; 
 int /*<<< orphan*/  debug (char*,char const) ; 
 int /*<<< orphan*/  isalnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
client_x11_display_valid(const char *display)
{
	size_t i, dlen;

	if (display == NULL)
		return 0;

	dlen = strlen(display);
	for (i = 0; i < dlen; i++) {
		if (!isalnum((u_char)display[i]) &&
		    strchr(SSH_X11_VALID_DISPLAY_CHARS, display[i]) == NULL) {
			debug("Invalid character '%c' in DISPLAY", display[i]);
			return 0;
		}
	}
	return 1;
}