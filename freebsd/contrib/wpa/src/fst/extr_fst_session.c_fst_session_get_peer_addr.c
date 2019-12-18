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
struct TYPE_2__ {int /*<<< orphan*/  const* new_peer_addr; int /*<<< orphan*/  const* old_peer_addr; } ;
struct fst_session {TYPE_1__ data; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */

const u8 * fst_session_get_peer_addr(struct fst_session *s, Boolean is_old)
{
	return is_old ? s->data.old_peer_addr : s->data.new_peer_addr;
}