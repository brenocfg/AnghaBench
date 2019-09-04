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
typedef  int /*<<< orphan*/  git_checkout_perfdata ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int) ; 

void perfdata_cb(const git_checkout_perfdata *in, void *payload)
{
	memcpy(payload, in, sizeof(git_checkout_perfdata));
}