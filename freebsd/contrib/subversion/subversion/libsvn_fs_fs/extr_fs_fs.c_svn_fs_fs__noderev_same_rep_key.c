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
typedef  int svn_boolean_t ;
struct TYPE_4__ {scalar_t__ item_index; scalar_t__ revision; int /*<<< orphan*/  uniquifier; } ;
typedef  TYPE_1__ representation_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

svn_boolean_t
svn_fs_fs__noderev_same_rep_key(representation_t *a,
                                representation_t *b)
{
  if (a == b)
    return TRUE;

  if (a == NULL || b == NULL)
    return FALSE;

  if (a->item_index != b->item_index)
    return FALSE;

  if (a->revision != b->revision)
    return FALSE;

  return memcmp(&a->uniquifier, &b->uniquifier, sizeof(a->uniquifier)) == 0;
}