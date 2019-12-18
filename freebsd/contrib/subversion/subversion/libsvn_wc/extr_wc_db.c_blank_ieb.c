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
struct TYPE_4__ {void* recorded_revision; void* recorded_peg_revision; int /*<<< orphan*/  repos_id; void* changed_rev; void* revision; } ;
typedef  TYPE_1__ insert_external_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_REPOS_ID ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
blank_ieb(insert_external_baton_t *ieb)
{
  memset(ieb, 0, sizeof(*ieb));
  ieb->revision = SVN_INVALID_REVNUM;
  ieb->changed_rev = SVN_INVALID_REVNUM;
  ieb->repos_id = INVALID_REPOS_ID;

  ieb->recorded_peg_revision = SVN_INVALID_REVNUM;
  ieb->recorded_revision = SVN_INVALID_REVNUM;
}