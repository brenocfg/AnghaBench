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
 int /*<<< orphan*/  NGM_TEXT_CONFIG ; 
 int NG_TEXTRESPONSE ; 
 scalar_t__ NgRecvMsg (int /*<<< orphan*/ ,struct ng_mesg* const,int,int /*<<< orphan*/ *) ; 
 int NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  csock ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
ConfigCmd(int ac, char **av)
{
	u_char sbuf[sizeof(struct ng_mesg) + NG_TEXTRESPONSE];
	struct ng_mesg *const resp = (struct ng_mesg *) sbuf;
	char *const status = (char *) resp->data;
	char *path;
	char buf[NG_TEXTRESPONSE];
	int nostat = 0, i;

	/* Get arguments */
	if (ac < 2)
		return (CMDRTN_USAGE);
	path = av[1];

	*buf = '\0';
	for (i = 2; i < ac; i++) {
		if (i != 2)
			strcat(buf, " ");
		strcat(buf, av[i]);
	}
	
	/* Get node config summary */
	if (*buf != '\0')
		i = NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	            NGM_TEXT_CONFIG, buf, strlen(buf) + 1);
	else
		i = NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	            NGM_TEXT_CONFIG, NULL, 0);
	if (i < 0) {
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
		printf("No config available for \"%s\"\n", path);
	else
		printf("Config for \"%s\":\n%s\n", path, status);
	return (CMDRTN_OK);
}