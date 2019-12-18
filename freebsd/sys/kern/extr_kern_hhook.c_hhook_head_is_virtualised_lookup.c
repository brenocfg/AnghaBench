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
typedef  int /*<<< orphan*/  uint32_t ;
struct hhook_head {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 struct hhook_head* hhook_head_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hhook_head_is_virtualised (struct hhook_head*) ; 
 int /*<<< orphan*/  hhook_head_release (struct hhook_head*) ; 

uint32_t
hhook_head_is_virtualised_lookup(int32_t hook_type, int32_t hook_id)
{
	struct hhook_head *hhh;
	uint32_t ret;

	hhh = hhook_head_get(hook_type, hook_id);

	if (hhh == NULL)
		return (0);

	ret = hhook_head_is_virtualised(hhh);
	hhook_head_release(hhh);

	return (ret);
}