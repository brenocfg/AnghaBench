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

/* Variables and functions */
#define  RB_ASKNAME 138 
#define  RB_CDROM 137 
#define  RB_DFLTROOT 136 
#define  RB_GDB 135 
#define  RB_KDB 134 
#define  RB_MULTIPLE 133 
#define  RB_MUTE 132 
#define  RB_PAUSE 131 
 int RB_PROBE ; 
#define  RB_SERIAL 130 
#define  RB_SINGLE 129 
#define  RB_VERBOSE 128 
 int /*<<< orphan*/  SETENV (char*,char*) ; 
 char* kargs ; 
 char* opts ; 
 void* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strsep (char**,char*) ; 
 char const* sw ; 

int
boot_parse_arg(char *v)
{
	char *n;
	int howto;

#if 0
/* Need to see if this is better or worse than the meat of the #else */
static const char howto_switches[] = "aCdrgDmphsv";
static int howto_masks[] = {
	RB_ASKNAME, RB_CDROM, RB_KDB, RB_DFLTROOT, RB_GDB, RB_MULTIPLE,
	RB_MUTE, RB_PAUSE, RB_SERIAL, RB_SINGLE, RB_VERBOSE
};

	opts = strchr(kargs, '-');
	while (opts != NULL) {
		while (*(++opts) != '\0') {
			sw = strchr(howto_switches, *opts);
			if (sw == NULL)
				break;
			howto |= howto_masks[sw - howto_switches];
		}
		opts = strchr(opts, '-');
	}
#else
	howto = 0;
	if (*v == '-') {
		while (*v != '\0') {
			v++;
			switch (*v) {
			case 'a': howto |= RB_ASKNAME; break;
			case 'C': howto |= RB_CDROM; break;
			case 'd': howto |= RB_KDB; break;
			case 'D': howto |= RB_MULTIPLE; break;
			case 'm': howto |= RB_MUTE; break;
			case 'g': howto |= RB_GDB; break;
			case 'h': howto |= RB_SERIAL; break;
			case 'p': howto |= RB_PAUSE; break;
			case 'P': howto |= RB_PROBE; break;
			case 'r': howto |= RB_DFLTROOT; break;
			case 's': howto |= RB_SINGLE; break;
			case 'S': SETENV("comconsole_speed", v + 1); v += strlen(v); break;
			case 'v': howto |= RB_VERBOSE; break;
			}
		}
	} else {
		n = strsep(&v, "=");
		if (v == NULL)
			SETENV(n, "1");
		else
			SETENV(n, v);
	}
#endif
	return (howto);
}