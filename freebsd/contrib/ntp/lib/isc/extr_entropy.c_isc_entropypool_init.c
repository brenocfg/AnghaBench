#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pool; scalar_t__ rotate; scalar_t__ pseudo; scalar_t__ entropy; scalar_t__ cursor; } ;
typedef  TYPE_1__ isc_entropypool_t ;

/* Variables and functions */
 int /*<<< orphan*/  RND_POOLBYTES ; 
 scalar_t__ RND_POOLWORDS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isc_entropypool_init(isc_entropypool_t *pool) {
	pool->cursor = RND_POOLWORDS - 1;
	pool->entropy = 0;
	pool->pseudo = 0;
	pool->rotate = 0;
	memset(pool->pool, 0, RND_POOLBYTES);
}