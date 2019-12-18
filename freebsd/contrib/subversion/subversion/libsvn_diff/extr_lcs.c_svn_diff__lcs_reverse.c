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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ svn_diff__lcs_t ;

/* Variables and functions */

__attribute__((used)) static svn_diff__lcs_t *
svn_diff__lcs_reverse(svn_diff__lcs_t *lcs)
{
  svn_diff__lcs_t *next;
  svn_diff__lcs_t *prev;

  next = NULL;
  while (lcs != NULL)
    {
      prev = lcs->next;
      lcs->next = next;
      next = lcs;
      lcs = prev;
    }

  return next;
}