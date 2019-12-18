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
typedef  int /*<<< orphan*/  u_int ;
struct rndtest_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RANDOM_PURE_HIFN ; 
 int /*<<< orphan*/  random_harvest_queue (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
default_harvest(struct rndtest_state *rsp, void *buf, u_int count)
{
	/* MarkM: FIX!! Check that this does not swamp the harvester! */
	random_harvest_queue(buf, count, RANDOM_PURE_HIFN);
}