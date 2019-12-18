#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  int pid_t ;
struct TYPE_3__ {int session; scalar_t__ uid; } ;
typedef  TYPE_1__ kcm_client ;

/* Variables and functions */

int
kcm_is_same_session(kcm_client *client, uid_t uid, pid_t session)
{
#if 0 /* XXX pppd is running in diffrent session the user */
    if (session != -1)
	return (client->session == session);
    else
#endif
	return  (client->uid == uid);
}