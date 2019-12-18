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
struct TYPE_4__ {int cch_sock; int cch_pd; int cch_flags; int /*<<< orphan*/  cch_magic; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CHANNEL_MAGIC ; 
 int CASPER_VALID_FLAGS ; 
 int /*<<< orphan*/  fd_is_valid (int) ; 
 TYPE_1__* malloc (int) ; 

cap_channel_t *
cap_wrap(int sock, int flags)
{
	cap_channel_t *chan;

	if (!fd_is_valid(sock))
		return (NULL);

	if ((flags & CASPER_VALID_FLAGS) != flags)
		return (NULL);

	chan = malloc(sizeof(*chan));
	if (chan != NULL) {
		chan->cch_sock = sock;
		chan->cch_pd = -1;
		chan->cch_flags = flags;
		chan->cch_magic = CAP_CHANNEL_MAGIC;
	}

	return (chan);
}