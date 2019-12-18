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
struct ng_mesg {int dummy; } ;

/* Variables and functions */
 int EFBIG ; 
 int ENOMEM ; 
 int EWOULDBLOCK ; 
 size_t LEAF_begemotNgMsgReadErrs ; 
 size_t LEAF_begemotNgNoMems ; 
 size_t LEAF_begemotNgTooLargeMsgs ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int NgRecvMsg (int /*<<< orphan*/ ,struct ng_mesg*,int,char*) ; 
 int /*<<< orphan*/  csock ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 struct ng_mesg* malloc (int) ; 
 int resbufsiz ; 
 int /*<<< orphan*/ * stats ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ng_mesg *
csock_read(char *path)
{
	struct ng_mesg *mesg;
	int ret, err;

	if ((mesg = malloc(resbufsiz + 1)) == NULL) {
		stats[LEAF_begemotNgNoMems]++;
		syslog(LOG_CRIT, "out of memory");
		errno = ENOMEM;
		return (NULL);
	}
	if ((ret = NgRecvMsg(csock, mesg, resbufsiz + 1, path)) < 0) {
		err = errno;
		free(mesg);
		if (errno == EWOULDBLOCK) {
			errno = err;
			return (NULL);
		}
		stats[LEAF_begemotNgMsgReadErrs]++;
		syslog(LOG_WARNING, "read from csock: %m");
		errno = err;
		return (NULL);
	}
	if (ret == 0) {
		syslog(LOG_DEBUG, "node closed -- exiting");
		exit(0);
	}
	if ((size_t)ret > resbufsiz) {
		stats[LEAF_begemotNgTooLargeMsgs]++;
		syslog(LOG_WARNING, "ng message too large");
		free(mesg);
		errno = EFBIG;
		return (NULL);
	}
	return (mesg);
}