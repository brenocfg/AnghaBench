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
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  recv (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_error_response(int fd, char *errbuf) {		/* return a pointer on error, NULL on no error */
	char	byte;
	int		len = 0;

	while (1) {
		recv(fd, &byte, 1, 0);							/* read another byte in */
		if (errbuf && (len++ < PCAP_ERRBUF_SIZE)) {		/* and if there is still room in the buffer */
			*errbuf++ = byte;							/* stick it in */
			*errbuf = '\0';								/* ensure the string is null terminated just in case we might exceed the buffer's size */
		}
		if (byte == '\0') {
			if (len > 1)	{ return errbuf;	}
			else			{ return NULL;		}
		}
	}
}