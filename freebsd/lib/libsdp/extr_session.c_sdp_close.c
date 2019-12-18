#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sdp_session_p ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {scalar_t__ s; struct TYPE_4__* rsp; struct TYPE_4__* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int32_t
sdp_close(void *xss)
{
	sdp_session_p	ss = (sdp_session_p) xss;

	if (ss != NULL) {
		if (ss->s >= 0)
			close(ss->s);

		if (ss->req != NULL)
			free(ss->req);
		if (ss->rsp != NULL)
			free(ss->rsp);

		memset(ss, 0, sizeof(*ss));
		free(ss);
	}

	return (0);
}