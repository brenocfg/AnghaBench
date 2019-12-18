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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EV_VOLATILE ; 
 int RB_MUTE ; 
 int RB_SERIAL ; 
 int boot_env_to_howto () ; 
 int boot_parse_cmdline (char*) ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bi_getboothowto(char *kargs)
{
	const char *sw, *tmp;
	char *opts;
	char *console;
	int howto, speed, port;
	char buf[50];

	howto = boot_parse_cmdline(kargs);
	howto |= boot_env_to_howto();

	console = getenv("console");
	if (console != NULL) {
		if (strcmp(console, "comconsole") == 0)
			howto |= RB_SERIAL;
		if (strcmp(console, "nullconsole") == 0)
			howto |= RB_MUTE;
#if defined(__i386__) || defined(__amd64__)
		if (strcmp(console, "efi") == 0 &&
		    getenv("efi_8250_uid") != NULL &&
		    getenv("hw.uart.console") == NULL) {
			/*
			 * If we found a 8250 com port and com speed, we need to
			 * tell the kernel where the serial port is, and how
			 * fast. Ideally, we'd get the port from ACPI, but that
			 * isn't running in the loader. Do the next best thing
			 * by allowing it to be set by a loader.conf variable,
			 * either a EFI specific one, or the compatible
			 * comconsole_port if not. PCI support is needed, but
			 * for that we'd ideally refactor the
			 * libi386/comconsole.c code to have identical behavior.
			 * We only try to set the port for cases where we saw
			 * the Serial(x) node when parsing, otherwise
			 * specialized hardware that has Uart nodes will have a
			 * bogus address set.
			 * But if someone specifically setup hw.uart.console,
			 * don't override that.
			 */
			speed = -1;
			port = -1;
			tmp = getenv("efi_com_speed");
			if (tmp != NULL)
				speed = strtol(tmp, NULL, 0);
			tmp = getenv("efi_com_port");
			if (tmp == NULL)
				tmp = getenv("comconsole_port");
			if (tmp != NULL)
				port = strtol(tmp, NULL, 0);
			if (speed != -1 && port != -1) {
				snprintf(buf, sizeof(buf), "io:%d,br:%d", port,
				    speed);
				env_setenv("hw.uart.console", EV_VOLATILE, buf,
				    NULL, NULL);
			}
		}
#endif
	}

	return (howto);
}