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
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_idnum ; 
 int /*<<< orphan*/  mark_object (struct object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mark_next_object(struct object *object)
{
	mark_object(object, ++last_idnum);
}