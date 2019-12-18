#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_tristate_t ;
typedef  scalar_t__ apr_uint64_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_tristate_false ; 
 int /*<<< orphan*/  svn_tristate_true ; 
 int /*<<< orphan*/  svn_tristate_unknown ; 

__attribute__((used)) static svn_tristate_t
optbool_to_tristate(apr_uint64_t v)
{
  if (v == TRUE)  /* not just non-zero but exactly equal to 'TRUE' */
    return svn_tristate_true;
  if (v == FALSE)
    return svn_tristate_false;

  return svn_tristate_unknown; /* Contains SVN_RA_SVN_UNSPECIFIED_NUMBER */
}