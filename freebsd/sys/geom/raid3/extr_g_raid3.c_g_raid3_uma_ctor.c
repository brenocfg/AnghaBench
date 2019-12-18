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
struct g_raid3_zone {scalar_t__ sz_max; scalar_t__ sz_inuse; } ;

/* Variables and functions */
 int ENOMEM ; 

__attribute__((used)) static int
g_raid3_uma_ctor(void *mem, int size, void *arg, int flags)
{
	struct g_raid3_zone *sz = arg;

	if (sz->sz_max > 0 && sz->sz_inuse == sz->sz_max)
		return (ENOMEM);
	sz->sz_inuse++;
	return (0);
}