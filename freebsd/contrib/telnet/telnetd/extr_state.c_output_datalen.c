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
 int BUFSIZ ; 
 int /*<<< orphan*/  memmove (int,char const*,int) ; 
 int /*<<< orphan*/  netflush () ; 
 int netobuf ; 
 int nfrontp ; 

void
output_datalen(const char *buf, int len)
{
	int remaining, copied;
	
	remaining = BUFSIZ - (nfrontp - netobuf);
	while (len > 0) {
		/* Free up enough space if the room is too low*/
		if ((len > BUFSIZ ? BUFSIZ : len) > remaining) {
			netflush();
			remaining = BUFSIZ - (nfrontp - netobuf);
		}

		/* Copy out as much as will fit */
		copied = remaining > len ? len : remaining;
		memmove(nfrontp, buf, copied);
		nfrontp += copied;
		len -= copied;
		remaining -= copied;
		buf += copied;
	}
	return;
}