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
struct sockaddr_l2cap {int /*<<< orphan*/  l2cap_bdaddr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  TYPE_1__* sdp_session_p ;
typedef  int /*<<< orphan*/  sa ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_2__ {int flags; scalar_t__ error; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int SDP_SESSION_LOCAL ; 
 int /*<<< orphan*/  bdaddr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

int32_t
sdp_get_lcaddr(void *xss, bdaddr_t *l)
{
	sdp_session_p		ss = (sdp_session_p) xss;
	struct sockaddr_l2cap	sa;
	socklen_t		size;

	if (l == NULL || ss == NULL || ss->flags & SDP_SESSION_LOCAL) {
		ss->error = EINVAL;
		goto fail;
	}

	size = sizeof(sa);
	if (getsockname(ss->s, (struct sockaddr *)&sa, &size) == 0) {
		bdaddr_copy(l, &sa.l2cap_bdaddr);
		ss->error = 0;
	} else
		ss->error = errno;
fail:
	return ((ss->error == 0) ? 0 : -1);
}