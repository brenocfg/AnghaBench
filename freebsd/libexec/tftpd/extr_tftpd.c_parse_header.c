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
struct formats {int /*<<< orphan*/ * f_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADOP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  exit (int) ; 
 struct formats* formats ; 
 int get_field (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isupper (char) ; 
 int /*<<< orphan*/  send_error (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,...) ; 
 char tolower (char) ; 

__attribute__((used)) static char *
parse_header(int peer, char *recvbuffer, ssize_t size,
	char **filename, char **mode)
{
	char	*cp;
	int	i;
	struct formats *pf;

	*mode = NULL;
	cp = recvbuffer;

	i = get_field(peer, recvbuffer, size);
	if (i >= PATH_MAX) {
		tftp_log(LOG_ERR, "Bad option - filename too long");
		send_error(peer, EBADOP);
		exit(1);
	}
	*filename = recvbuffer;
	tftp_log(LOG_INFO, "Filename: '%s'", *filename);
	cp += i;

	i = get_field(peer, cp, size);
	*mode = cp;
	cp += i;

	/* Find the file transfer mode */
	for (cp = *mode; *cp; cp++)
		if (isupper(*cp))
			*cp = tolower(*cp);
	for (pf = formats; pf->f_mode; pf++)
		if (strcmp(pf->f_mode, *mode) == 0)
			break;
	if (pf->f_mode == NULL) {
		tftp_log(LOG_ERR,
		    "Bad option - Unknown transfer mode (%s)", *mode);
		send_error(peer, EBADOP);
		exit(1);
	}
	tftp_log(LOG_INFO, "Mode: '%s'", *mode);

	return (cp + 1);
}