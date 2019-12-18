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
struct peer {scalar_t__ selbroken; scalar_t__ seldisptoolarge; scalar_t__ oldpkt; scalar_t__ bogusorg; scalar_t__ badauth; scalar_t__ processed; scalar_t__ received; scalar_t__ sent; int /*<<< orphan*/  timereset; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_time ; 

void
peer_reset(
	struct peer *peer
	)
{
	if (peer == NULL)
		return;

	peer->timereset = current_time;
	peer->sent = 0;
	peer->received = 0;
	peer->processed = 0;
	peer->badauth = 0;
	peer->bogusorg = 0;
	peer->oldpkt = 0;
	peer->seldisptoolarge = 0;
	peer->selbroken = 0;
}