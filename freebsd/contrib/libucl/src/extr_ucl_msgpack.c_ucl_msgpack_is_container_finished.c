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
typedef  int uint64_t ;
struct ucl_stack {int level; } ;

/* Variables and functions */
 int MSGPACK_CONTAINER_BIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ucl_msgpack_is_container_finished (struct ucl_stack *container)
{
	uint64_t level;

	assert (container != NULL);

	if (container->level & MSGPACK_CONTAINER_BIT) {
		level = container->level & ~MSGPACK_CONTAINER_BIT;

		if (level == 0) {
			return true;
		}
	}

	return false;
}