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
struct blk_buf {int dummy; } ;

/* Variables and functions */
 struct blk_buf* xcalloc (int,int) ; 

struct blk_buf *
bb_alloc(void)
{
    return xcalloc(1, sizeof(struct blk_buf));
}