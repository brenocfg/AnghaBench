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
struct TYPE_4__ {scalar_t__ rev; int /*<<< orphan*/  relpath; } ;
typedef  TYPE_1__ svn_pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t
pathrev_equal(const svn_pathrev_t *p1,
              const svn_pathrev_t *p2)
{
  if (p1->rev != p2->rev)
    return FALSE;
  if (strcmp(p1->relpath, p2->relpath) != 0)
    return FALSE;

  return TRUE;
}