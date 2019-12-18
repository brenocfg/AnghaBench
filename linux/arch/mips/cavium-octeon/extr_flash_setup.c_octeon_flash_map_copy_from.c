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
struct map_info {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inline_map_copy_from (struct map_info*,void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_bootbus_sem ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void octeon_flash_map_copy_from(struct map_info *map, void *to,
				       unsigned long from, ssize_t len)
{
	down(&octeon_bootbus_sem);
	inline_map_copy_from(map, to, from, len);
	up(&octeon_bootbus_sem);
}