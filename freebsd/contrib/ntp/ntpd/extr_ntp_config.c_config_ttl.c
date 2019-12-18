#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_5__ {scalar_t__ i; struct TYPE_5__* link; } ;
typedef  TYPE_1__ int_node ;
struct TYPE_6__ {int /*<<< orphan*/  ttl; } ;
typedef  TYPE_2__ config_tree ;

/* Variables and functions */
 size_t COUNTOF (scalar_t__*) ; 
 TYPE_1__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,size_t,scalar_t__) ; 
 scalar_t__* sys_ttl ; 
 size_t sys_ttlmax ; 

__attribute__((used)) static void
config_ttl(
	config_tree *ptree
	)
{
	size_t i = 0;
	int_node *curr_ttl;

	/* [Bug 3465] There is a built-in default for the TTLs. We must
	 * overwrite 'sys_ttlmax' if we change that preset, and leave it
	 * alone otherwise!
	 */
	curr_ttl = HEAD_PFIFO(ptree->ttl);
	for (; curr_ttl != NULL; curr_ttl = curr_ttl->link) {
		if (i < COUNTOF(sys_ttl))
			sys_ttl[i++] = (u_char)curr_ttl->i;
		else
			msyslog(LOG_INFO,
				"ttl: Number of TTL entries exceeds %zu. Ignoring TTL %d...",
				COUNTOF(sys_ttl), curr_ttl->i);
	}
	if (0 != i) /* anything written back at all? */
		sys_ttlmax = i - 1;
}