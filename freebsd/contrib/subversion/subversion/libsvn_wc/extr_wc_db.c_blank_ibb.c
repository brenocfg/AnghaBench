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
struct TYPE_4__ {int /*<<< orphan*/  repos_id; int /*<<< orphan*/  depth; void* changed_rev; void* revision; } ;
typedef  TYPE_1__ insert_base_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_REPOS_ID ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 

__attribute__((used)) static void
blank_ibb(insert_base_baton_t *pibb)
{
  memset(pibb, 0, sizeof(*pibb));
  pibb->revision = SVN_INVALID_REVNUM;
  pibb->changed_rev = SVN_INVALID_REVNUM;
  pibb->depth = svn_depth_infinity;
  pibb->repos_id = INVALID_REPOS_ID;
}