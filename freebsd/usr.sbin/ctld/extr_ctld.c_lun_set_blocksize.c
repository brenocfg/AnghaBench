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
struct lun {size_t l_blocksize; } ;

/* Variables and functions */

void
lun_set_blocksize(struct lun *lun, size_t value)
{

	lun->l_blocksize = value;
}