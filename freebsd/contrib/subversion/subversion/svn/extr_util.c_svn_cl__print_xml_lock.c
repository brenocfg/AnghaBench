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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_3__ {scalar_t__ creation_date; scalar_t__ expiration_date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  svn_cl__xml_tagged_cdata (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_to_cstring (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_normal ; 

void
svn_cl__print_xml_lock(svn_stringbuf_t **sb,
                       const svn_lock_t *lock,
                       apr_pool_t *pool)
{
  /* "<lock>" */
  svn_xml_make_open_tag(sb, pool, svn_xml_normal, "lock", SVN_VA_NULL);

  /* "<token>xx</token>" */
  svn_cl__xml_tagged_cdata(sb, pool, "token", lock->token);

  /* "<owner>xx</owner>" */
  svn_cl__xml_tagged_cdata(sb, pool, "owner", lock->owner);

  /* "<comment>xx</comment>" */
  svn_cl__xml_tagged_cdata(sb, pool, "comment", lock->comment);

  /* "<created>xx</created>" */
  svn_cl__xml_tagged_cdata(sb, pool, "created",
                           svn_time_to_cstring(lock->creation_date, pool));

  /* "<expires>xx</expires>" */
  if (lock->expiration_date != 0)
    svn_cl__xml_tagged_cdata(sb, pool, "expires",
                             svn_time_to_cstring(lock->expiration_date, pool));

  /* "</lock>" */
  svn_xml_make_close_tag(sb, pool, "lock");
}