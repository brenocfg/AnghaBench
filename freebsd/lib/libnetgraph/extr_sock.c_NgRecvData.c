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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_ng {int /*<<< orphan*/  sg_data; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  frombuf ;

/* Variables and functions */
 int /*<<< orphan*/  NGLOG (char*) ; 
 int /*<<< orphan*/  NGLOGX (char*,char*,int /*<<< orphan*/ ,int) ; 
 int NGSA_OVERHEAD ; 
 int NG_HOOKSIZ ; 
 int /*<<< orphan*/  _NgDebugBytes (int /*<<< orphan*/ *,int) ; 
 int _gNgDebugLevel ; 
 int errno ; 
 int recvfrom (int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int
NgRecvData(int ds, u_char * buf, size_t len, char *hook)
{
	u_char frombuf[NG_HOOKSIZ + NGSA_OVERHEAD];
	struct sockaddr_ng *const from = (struct sockaddr_ng *) frombuf;
	socklen_t fromlen = sizeof(frombuf);
	int rtn, errnosv;

	/* Read packet */
	rtn = recvfrom(ds, buf, len, 0, (struct sockaddr *) from, &fromlen);
	if (rtn < 0) {
		errnosv = errno;
		if (_gNgDebugLevel >= 1)
			NGLOG("recvfrom");
		errno = errnosv;
		return (-1);
	}

	/* Copy hook name */
	if (hook != NULL)
		strlcpy(hook, from->sg_data, NG_HOOKSIZ);

	/* Debugging */
	if (_gNgDebugLevel >= 2) {
		NGLOGX("READ %s from hook \"%s\" (%d bytes)",
		       rtn ? "PACKET" : "EOF", from->sg_data, rtn);
		if (_gNgDebugLevel >= 3)
			_NgDebugBytes(buf, rtn);
	}

	/* Done */
	return (rtn);
}