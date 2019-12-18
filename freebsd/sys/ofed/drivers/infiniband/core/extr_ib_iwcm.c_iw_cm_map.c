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
struct iw_cm_id {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  m_remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  m_local_addr; } ;

/* Variables and functions */

__attribute__((used)) static int iw_cm_map(struct iw_cm_id *cm_id, bool active)
{
	cm_id->m_local_addr = cm_id->local_addr;
	cm_id->m_remote_addr = cm_id->remote_addr;

	return 0;
}