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
struct rsocket {int dummy; } ;
struct rs_svc {int cnt; struct rsocket** rss; } ;

/* Variables and functions */

__attribute__((used)) static int rs_svc_index(struct rs_svc *svc, struct rsocket *rs)
{
	int i;

	for (i = 1; i <= svc->cnt; i++) {
		if (svc->rss[i] == rs)
			return i;
	}
	return -1;
}