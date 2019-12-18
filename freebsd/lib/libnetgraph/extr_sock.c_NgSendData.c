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
struct sockaddr_ng {int sg_len; int /*<<< orphan*/  sg_data; int /*<<< orphan*/  sg_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETGRAPH ; 
 int /*<<< orphan*/  NGLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLOGX (char*,char const*,size_t) ; 
 int NGSA_OVERHEAD ; 
 int NG_HOOKSIZ ; 
 int /*<<< orphan*/  _NgDebugBytes (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  _NgDebugSockaddr (struct sockaddr_ng* const) ; 
 int _gNgDebugLevel ; 
 int errno ; 
 scalar_t__ sendto (int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int
NgSendData(int ds, const char *hook, const u_char * buf, size_t len)
{
	u_char sgbuf[NG_HOOKSIZ + NGSA_OVERHEAD];
	struct sockaddr_ng *const sg = (struct sockaddr_ng *) sgbuf;
	int errnosv;

	/* Set up destination hook */
	sg->sg_family = AF_NETGRAPH;
	strlcpy(sg->sg_data, hook, NG_HOOKSIZ);
	sg->sg_len = strlen(sg->sg_data) + 1 + NGSA_OVERHEAD;

	/* Debugging */
	if (_gNgDebugLevel >= 2) {
		NGLOGX("WRITE PACKET to hook \"%s\" (%d bytes)", hook, len);
		_NgDebugSockaddr(sg);
		if (_gNgDebugLevel >= 3)
			_NgDebugBytes(buf, len);
	}

	/* Send packet */
	if (sendto(ds, buf, len, 0, (struct sockaddr *) sg, sg->sg_len) < 0) {
		errnosv = errno;
		if (_gNgDebugLevel >= 1)
			NGLOG("sendto(%s)", sg->sg_data);
		errno = errnosv;
		return (-1);
	}

	/* Done */
	return (0);
}