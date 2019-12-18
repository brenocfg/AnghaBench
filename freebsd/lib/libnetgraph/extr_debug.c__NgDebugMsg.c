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
struct TYPE_2__ {int version; int arglen; int flags; int token; int cmd; int /*<<< orphan*/  cmdstr; int /*<<< orphan*/  typecookie; } ;
struct ng_mesg {int data; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ARGS_BUFSIZE ; 
 int /*<<< orphan*/  NGLOGX (char*,...) ; 
 int /*<<< orphan*/  NGM_BINARY2ASCII ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NgCookie (int /*<<< orphan*/ ) ; 
 scalar_t__ NgMkSockNode (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ NgRecvMsg (int,struct ng_mesg* const,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NgSendMsg (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_mesg* const,int) ; 
 scalar_t__ RECURSIVE_DEBUG_ADJUST ; 
 int /*<<< orphan*/  _NgDebugBytes (int /*<<< orphan*/ *,int) ; 
 int _gNgDebugLevel ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (struct ng_mesg* const,struct ng_mesg const*,int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int strerror (int /*<<< orphan*/ ) ; 

void
_NgDebugMsg(const struct ng_mesg *msg, const char *path)
{
	u_char buf[2 * sizeof(struct ng_mesg) + ARGS_BUFSIZE];
	struct ng_mesg *const req = (struct ng_mesg *)buf;
	struct ng_mesg *const bin = (struct ng_mesg *)req->data;
	int arglen, csock = -1;

	/* Display header stuff */
	NGLOGX("NG_MESG :");
	NGLOGX("  vers   %d", msg->header.version);
	NGLOGX("  arglen %u", msg->header.arglen);
	NGLOGX("  flags  %x", msg->header.flags);
	NGLOGX("  token  %u", msg->header.token);
	NGLOGX("  cookie %s (%u)",
	    NgCookie(msg->header.typecookie), msg->header.typecookie);

	/* At lower debugging levels, skip ASCII translation */
	if (_gNgDebugLevel <= 2)
		goto fail2;

	/* If path is not absolute, don't bother trying to use relative
	   address on a different socket for the ASCII translation */
	if (strchr(path, ':') == NULL)
		goto fail2;

	/* Get a temporary socket */
	if (NgMkSockNode(NULL, &csock, NULL) < 0)
		goto fail;

	/* Copy binary message into request message payload */
	arglen = msg->header.arglen;
	if (arglen > ARGS_BUFSIZE)
		arglen = ARGS_BUFSIZE;
	memcpy(bin, msg, sizeof(*msg) + arglen);
	bin->header.arglen = arglen;

	/* Lower debugging to avoid infinite recursion */
	_gNgDebugLevel -= RECURSIVE_DEBUG_ADJUST;

	/* Ask the node to translate the binary message to ASCII for us */
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_BINARY2ASCII, bin, sizeof(*bin) + bin->header.arglen) < 0) {
		_gNgDebugLevel += RECURSIVE_DEBUG_ADJUST;
		goto fail;
	}
	if (NgRecvMsg(csock, req, sizeof(buf), NULL) < 0) {
		_gNgDebugLevel += RECURSIVE_DEBUG_ADJUST;
		goto fail;
	}

	/* Restore debugging level */
	_gNgDebugLevel += RECURSIVE_DEBUG_ADJUST;

	/* Display command string and arguments */
	NGLOGX("  cmd    %s (%d)", bin->header.cmdstr, bin->header.cmd);
	NGLOGX("  args   %s", bin->data);
	goto done;

fail:
	/* Just display binary version */
	NGLOGX("  [error decoding message: %s]", strerror(errno));
fail2:
	NGLOGX("  cmd    %d", msg->header.cmd);
	NGLOGX("  args (%d bytes)", msg->header.arglen);
	_NgDebugBytes((u_char *)msg->data, msg->header.arglen);

done:
	if (csock != -1)
		(void)close(csock);
}