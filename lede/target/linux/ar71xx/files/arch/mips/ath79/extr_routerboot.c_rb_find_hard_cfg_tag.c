#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  hard_cfg_size; int /*<<< orphan*/  hard_cfg_data; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__ rb_info ; 
 int routerboot_find_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
rb_find_hard_cfg_tag(u16 tag_id, u8 **tag_data, u16 *tag_len)
{
	if (!rb_info.hard_cfg_data ||
	    !rb_info.hard_cfg_size)
		return -ENOENT;

	return routerboot_find_tag(rb_info.hard_cfg_data,
				   rb_info.hard_cfg_size,
				   tag_id, tag_data, tag_len);
}