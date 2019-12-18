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
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ *,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idnums ; 
 int /*<<< orphan*/  mark_to_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mark_object(struct object *object, uint32_t mark)
{
	add_decoration(&idnums, object, mark_to_ptr(mark));
}