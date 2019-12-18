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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 char* convbuffer ; 
 int /*<<< orphan*/  file ; 
 int fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int gotcr ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static size_t
convert_from_net(char *buffer, size_t count)
{
	size_t i, n;

	/*
	 * Convert all CR/LF to LF and all CR,NUL to CR
	 */

	n = 0;
	for (i = 0; i < count; i++) {

		if (gotcr == 0) {
			convbuffer[n++] = buffer[i];
			gotcr = (buffer[i] == '\r');
			continue;
		}

		/* CR, NULL -> CR */
		if (buffer[i] == '\0') {
			gotcr = 0;
			continue;
		}

		/* CR, LF -> LF */
		if (buffer[i] == '\n') {
			if (n == 0) {
				if (ftell(file) != 0) {
					int r = fseek(file, -1, SEEK_END);
					assert(r == 0);
					convbuffer[n++] = '\n';
				} else {
					/* This shouldn't happen */
					tftp_log(LOG_ERR,
					    "Received LF as first character");
					abort();
				}
			} else
				convbuffer[n-1] = '\n';
			gotcr = 0;
			continue;
		}

		/* Everything else just accept as is */
		convbuffer[n++] = buffer[i];
		gotcr = (buffer[i] == '\r');
		continue;
	}

	return fwrite(convbuffer, 1, n, file);
}