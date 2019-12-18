#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* data; TYPE_2__* prefix; } ;
typedef  TYPE_1__ svn_prefix_string__t ;
struct TYPE_6__ {scalar_t__ length; TYPE_1__ key; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int
svn_prefix_string__compare(const svn_prefix_string__t *lhs,
                           const svn_prefix_string__t *rhs)
{
  const node_t *lhs_parent = lhs->prefix;
  const node_t *rhs_parent = rhs->prefix;

  if (lhs == rhs)
    return 0;

  /* find the common root */
  while (lhs_parent != rhs_parent)
    {
      if (lhs_parent->length <= rhs_parent->length)
        {
          rhs = &rhs_parent->key;
          rhs_parent = rhs_parent->key.prefix;
        }
      else if (rhs_parent->length <= lhs_parent->length)
        {
          lhs = &lhs_parent->key;
          lhs_parent = lhs_parent->key.prefix;
        }

      /* same tree? */
      assert(lhs_parent && rhs_parent);
    }

  /* at the common root, strings will differ in the first follow-up char */
  return (int)(unsigned char)lhs->data[0] - (int)(unsigned char)rhs->data[0];
}