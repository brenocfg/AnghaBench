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
struct TYPE_4__ {scalar_t__ parent_eid; int /*<<< orphan*/  payload; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_element__content_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_element__payload_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_element__content_equal(const svn_element__content_t *content_left,
                           const svn_element__content_t *content_right,
                           apr_pool_t *scratch_pool)
{
  if (!content_left && !content_right)
    {
      return TRUE;
    }
  else if (!content_left || !content_right)
    {
      return FALSE;
    }

  if (content_left->parent_eid != content_right->parent_eid)
    {
      return FALSE;
    }
  if (strcmp(content_left->name, content_right->name) != 0)
    {
      return FALSE;
    }
  if (! svn_element__payload_equal(content_left->payload, content_right->payload,
                                   scratch_pool))
    {
      return FALSE;
    }

  return TRUE;
}