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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ieee802_1x_kay_peer {scalar_t__ key_server_priority; TYPE_1__ sci; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_priorities(const struct ieee802_1x_kay_peer *peer,
			      const struct ieee802_1x_kay_peer *other)
{
	if (peer->key_server_priority < other->key_server_priority)
		return -1;
	if (other->key_server_priority < peer->key_server_priority)
		return 1;

	return os_memcmp(peer->sci.addr, other->sci.addr, ETH_ALEN);
}