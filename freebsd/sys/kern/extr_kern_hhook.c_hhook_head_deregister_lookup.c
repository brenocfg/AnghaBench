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
struct hhook_head {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EBUSY ; 
 int hhook_head_deregister (struct hhook_head*) ; 
 struct hhook_head* hhook_head_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hhook_head_release (struct hhook_head*) ; 

int
hhook_head_deregister_lookup(int32_t hhook_type, int32_t hhook_id)
{
	struct hhook_head *hhh;
	int error;

	hhh = hhook_head_get(hhook_type, hhook_id);
	error = hhook_head_deregister(hhh);

	if (error == EBUSY)
		hhook_head_release(hhh);

	return (error);
}