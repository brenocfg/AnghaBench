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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADOP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*) ; 

ssize_t
get_field(int peer, char *buffer, ssize_t size)
{
	char *cp = buffer;

	while (cp < buffer + size) {
		if (*cp == '\0') break;
		cp++;
	}
	if (*cp != '\0') {
		tftp_log(LOG_ERR, "Bad option - no trailing \\0 found");
		send_error(peer, EBADOP);
		exit(1);
	}
	return (cp - buffer + 1);
}