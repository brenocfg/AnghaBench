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
struct test_sglist {int /*<<< orphan*/  bufs; } ;

/* Variables and functions */
 int __testmgr_alloc_buf (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_test_sglist(struct test_sglist *tsgl)
{
	return __testmgr_alloc_buf(tsgl->bufs, 1 /* two pages per buffer */);
}