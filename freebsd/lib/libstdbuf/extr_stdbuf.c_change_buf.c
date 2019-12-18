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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int _IOFBF ; 
 int _IOLBF ; 
 int _IONBF ; 
 scalar_t__ errno ; 
 scalar_t__ setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  stream_name (int /*<<< orphan*/ *) ; 
 size_t strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
change_buf(FILE *s, const char *bufmode)
{
	char *unit;
	size_t bufsize;
	int mode;

	bufsize = 0;
	if (bufmode[0] == '0' && bufmode[1] == '\0')
		mode = _IONBF;
	else if (bufmode[0] == 'L' && bufmode[1] == '\0')
		mode = _IOLBF;
	else if (bufmode[0] == 'B' && bufmode[1] == '\0') {
		mode = _IOFBF;
		bufsize = 0;
	} else {
		/*
		 * This library being preloaded, depending on libutil
		 * would lead to excessive namespace pollution.
		 * Thus we do not use expand_number().
		 */
		errno = 0;
		bufsize = strtol(bufmode, &unit, 0);
		if (errno == EINVAL || errno == ERANGE || unit == bufmode)
			warn("Wrong buffer mode '%s' for %s", bufmode,
			    stream_name(s));
		switch (*unit) {
		case 'G':
			bufsize *= 1024 * 1024 * 1024;
			break;
		case 'M':
			bufsize *= 1024 * 1024;
			break;
		case 'k':
			bufsize *= 1024;
			break;
		case '\0':
			break;
		default:
			warnx("Unknown suffix '%c' for %s", *unit,
			    stream_name(s));
			return;
		}
		mode = _IOFBF;
	}
	if (setvbuf(s, NULL, mode, bufsize) != 0)
		warn("Cannot set buffer mode '%s' for %s", bufmode,
		    stream_name(s));
}