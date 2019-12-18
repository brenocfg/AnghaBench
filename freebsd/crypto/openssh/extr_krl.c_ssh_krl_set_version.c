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
typedef  int /*<<< orphan*/  u_int64_t ;
struct ssh_krl {int /*<<< orphan*/  krl_version; } ;

/* Variables and functions */

void
ssh_krl_set_version(struct ssh_krl *krl, u_int64_t version)
{
	krl->krl_version = version;
}