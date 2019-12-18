#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uuid_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_uuid ) (TYPE_2__*,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_UUID ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_uuid_parse (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 char* svn_uuid_generate (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_set_uuid(svn_fs_t *fs, const char *uuid, apr_pool_t *pool)
{
  if (! uuid)
    {
      uuid = svn_uuid_generate(pool);
    }
  else
    {
      apr_uuid_t parsed_uuid;
      apr_status_t apr_err = apr_uuid_parse(&parsed_uuid, uuid);
      if (apr_err)
        return svn_error_createf(SVN_ERR_BAD_UUID, NULL,
                                 _("Malformed UUID '%s'"), uuid);
    }
  return svn_error_trace(fs->vtable->set_uuid(fs, uuid, pool));
}