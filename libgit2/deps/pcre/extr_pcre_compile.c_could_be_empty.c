#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pcre_uchar ;
typedef  int /*<<< orphan*/  compile_data ;
struct TYPE_3__ {struct TYPE_3__* outer; int /*<<< orphan*/  const* current_branch; } ;
typedef  TYPE_1__ branch_chain ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  could_be_empty_branch (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
could_be_empty(const pcre_uchar *code, const pcre_uchar *endcode,
  branch_chain *bcptr, BOOL utf, compile_data *cd)
{
while (bcptr != NULL && bcptr->current_branch >= code)
  {
  if (!could_be_empty_branch(bcptr->current_branch, endcode, utf, cd, NULL))
    return FALSE;
  bcptr = bcptr->outer;
  }
return TRUE;
}