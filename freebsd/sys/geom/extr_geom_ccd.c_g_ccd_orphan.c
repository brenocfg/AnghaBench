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
struct g_consumer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
g_ccd_orphan(struct g_consumer *cp)
{
	/*
	 * XXX: We don't do anything here.  It is not obvious
	 * XXX: what DTRT would be, so we do what the previous
	 * XXX: code did: ignore it and let the user cope.
	 */
}