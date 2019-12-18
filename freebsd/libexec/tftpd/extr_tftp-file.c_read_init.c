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
 int /*<<< orphan*/  LOG_ERR ; 
 int convert ; 
 int /*<<< orphan*/  convert_to_net (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * file ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
read_init(int fd, FILE *f, const char *mode)
{

	convert_to_net(NULL, 0, 1);
	if (f == NULL) {
		file = fdopen(fd, "r");
		if (file == NULL) {
			int en = errno;
			tftp_log(LOG_ERR, "fdopen() failed: %s",
			    strerror(errno));
			return en;
		}
	} else
		file = f;
	convert = !strcmp(mode, "netascii");
	return 0;
}