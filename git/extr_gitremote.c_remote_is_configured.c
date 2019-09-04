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
struct remote {int configured_in_repo; int /*<<< orphan*/  origin; } ;

/* Variables and functions */

int remote_is_configured(struct remote *remote, int in_repo)
{
	if (!remote)
		return 0;
	if (in_repo)
		return remote->configured_in_repo;
	return !!remote->origin;
}