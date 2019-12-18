#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int flags; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
#define  EINVAL 128 
 int NGF_RESP ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_TEXT_STATUS ; 
 int /*<<< orphan*/  NG_TEXTRESPONSE ; 
 scalar_t__ NgRecvMsg (int /*<<< orphan*/ ,struct ng_mesg* const,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csock ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
StatusCmd(int ac, char **av)
{
	u_char sbuf[sizeof(struct ng_mesg) + NG_TEXTRESPONSE];
	struct ng_mesg *const resp = (struct ng_mesg *) sbuf;
	char *const status = (char *) resp->data;
	char *path;
	int nostat = 0;

	/* Get arguments */
	switch (ac) {
	case 2:
		path = av[1];
		break;
	default:
		return (CMDRTN_USAGE);
	}

	/* Get node status summary */
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_TEXT_STATUS, NULL, 0) < 0) {
		switch (errno) {
		case EINVAL:
			nostat = 1;
			break;
		default:
			warn("send msg");
			return (CMDRTN_ERROR);
		}
	} else {
		if (NgRecvMsg(csock, resp, sizeof(sbuf), NULL) < 0
		    || (resp->header.flags & NGF_RESP) == 0)
			nostat = 1;
	}

	/* Show it */
	if (nostat)
		printf("No status available for \"%s\"\n", path);
	else
		printf("Status for \"%s\":\n%s\n", path, status);
	return (CMDRTN_OK);
}