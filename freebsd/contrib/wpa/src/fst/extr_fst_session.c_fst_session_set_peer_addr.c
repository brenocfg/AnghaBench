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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * new_peer_addr; int /*<<< orphan*/ * old_peer_addr; } ;
struct fst_session {TYPE_1__ data; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void fst_session_set_peer_addr(struct fst_session *s, const u8 *addr,
			       Boolean is_old)
{
	u8 *a = is_old ? s->data.old_peer_addr : s->data.new_peer_addr;

	os_memcpy(a, addr, ETH_ALEN);
}