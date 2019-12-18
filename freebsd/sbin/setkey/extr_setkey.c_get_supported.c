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

/* Variables and functions */
 int /*<<< orphan*/  SADB_SATYPE_UNSPEC ; 
 scalar_t__ pfkey_recv_register (int /*<<< orphan*/ ) ; 
 scalar_t__ pfkey_send_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so ; 

int
get_supported()
{

	if (pfkey_send_register(so, SADB_SATYPE_UNSPEC) < 0)
		return -1;

	if (pfkey_recv_register(so) < 0)
		return -1;

	return 0;
}