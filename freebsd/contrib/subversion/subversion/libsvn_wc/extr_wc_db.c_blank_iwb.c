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
struct TYPE_4__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  changed_rev; } ;
typedef  TYPE_1__ insert_working_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 

__attribute__((used)) static void
blank_iwb(insert_working_baton_t *piwb)
{
  memset(piwb, 0, sizeof(*piwb));
  piwb->changed_rev = SVN_INVALID_REVNUM;
  piwb->depth = svn_depth_infinity;

  /* ORIGINAL_REPOS_ID and ORIGINAL_REVNUM could use some kind of "nil"
     value, but... meh. We'll avoid them if ORIGINAL_REPOS_RELPATH==NULL.  */
}