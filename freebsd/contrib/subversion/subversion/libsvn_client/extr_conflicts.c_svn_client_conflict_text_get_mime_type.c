#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
struct TYPE_7__ {char const* mime_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 scalar_t__ SVN_NO_ERROR ; 
 scalar_t__ assert_text_conflict (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* get_conflict_desc2_t (TYPE_1__*) ; 

const char *
svn_client_conflict_text_get_mime_type(svn_client_conflict_t *conflict)
{
  SVN_ERR_ASSERT_NO_RETURN(assert_text_conflict(conflict, conflict->pool)
                           == SVN_NO_ERROR);

  return get_conflict_desc2_t(conflict)->mime_type;
}