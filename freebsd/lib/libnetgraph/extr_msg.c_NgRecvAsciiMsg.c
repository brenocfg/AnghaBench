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
struct TYPE_2__ {int arglen; } ;
struct ng_mesg {TYPE_1__ header; scalar_t__ data; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  NGM_BINARY2ASCII ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 scalar_t__ NgRecvMsg (int,struct ng_mesg*,int,char*) ; 
 scalar_t__ NgSendMsg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg*,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct ng_mesg*,struct ng_mesg*,int) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,scalar_t__,int) ; 

int
NgRecvAsciiMsg(int cs, struct ng_mesg *reply, size_t replen, char *path)
{
	struct ng_mesg *msg, *ascii;
	int bufSize, errnosv;
	u_char *buf;

	/* Allocate buffer */
	bufSize = 2 * sizeof(*reply) + replen;
	if ((buf = malloc(bufSize)) == NULL)
		return (-1);
	msg = (struct ng_mesg *)buf;
	ascii = (struct ng_mesg *)msg->data;

	/* Get binary message */
	if (NgRecvMsg(cs, msg, bufSize, path) < 0)
		goto fail;
	memcpy(reply, msg, sizeof(*msg));

	/* Ask originating node to convert the arguments to ASCII */
	if (NgSendMsg(cs, path, NGM_GENERIC_COOKIE,
	    NGM_BINARY2ASCII, msg, sizeof(*msg) + msg->header.arglen) < 0)
		goto fail;
	if (NgRecvMsg(cs, msg, bufSize, NULL) < 0)
		goto fail;

	/* Copy result to client buffer */
	if (sizeof(*ascii) + ascii->header.arglen > replen) {
		errno = ERANGE;
fail:
		errnosv = errno;
		free(buf);
		errno = errnosv;
		return (-1);
	}
	strncpy(reply->data, ascii->data, ascii->header.arglen);

	/* Done */
	free(buf);
	return (0);
}