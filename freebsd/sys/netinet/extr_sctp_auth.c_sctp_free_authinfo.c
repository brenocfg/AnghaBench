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
struct TYPE_3__ {int /*<<< orphan*/ * recv_key; int /*<<< orphan*/ * assoc_key; int /*<<< orphan*/ * peer_random; int /*<<< orphan*/ * random; } ;
typedef  TYPE_1__ sctp_authinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_free_key (int /*<<< orphan*/ *) ; 

void
sctp_free_authinfo(sctp_authinfo_t *authinfo)
{
	if (authinfo == NULL)
		return;

	if (authinfo->random != NULL)
		sctp_free_key(authinfo->random);
	if (authinfo->peer_random != NULL)
		sctp_free_key(authinfo->peer_random);
	if (authinfo->assoc_key != NULL)
		sctp_free_key(authinfo->assoc_key);
	if (authinfo->recv_key != NULL)
		sctp_free_key(authinfo->recv_key);

	/* We are NOT dynamically allocating authinfo's right now... */
	/* SCTP_FREE(authinfo, SCTP_M_AUTH_??); */
}