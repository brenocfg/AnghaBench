#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ git_rawobj ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cmp_objects(git_rawobj *o1, git_rawobj *o2)
{
   cl_assert(o1->type == o2->type);
   cl_assert(o1->len == o2->len);
   if (o1->len > 0)
      cl_assert(memcmp(o1->data, o2->data, o1->len) == 0);
}