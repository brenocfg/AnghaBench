#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_10__ {void* instance_id; int /*<<< orphan*/  flush_to_disk; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; void* uuid; TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_x__path_current (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_uuid (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_atomic2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char const*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 char* svn_uuid_generate (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__set_uuid(svn_fs_t *fs,
                   const char *uuid,
                   const char *instance_id,
                   svn_boolean_t overwrite,
                   apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  const char *uuid_path = svn_fs_x__path_uuid(fs, scratch_pool);
  svn_stringbuf_t *contents = svn_stringbuf_create_empty(scratch_pool);

  if (! uuid)
    uuid = svn_uuid_generate(scratch_pool);

  if (! instance_id)
    instance_id = svn_uuid_generate(scratch_pool);

  svn_stringbuf_appendcstr(contents, uuid);
  svn_stringbuf_appendcstr(contents, "\n");
  svn_stringbuf_appendcstr(contents, instance_id);
  svn_stringbuf_appendcstr(contents, "\n");

  /* We use the permissions of the 'current' file, because the 'uuid'
     file does not exist during repository creation.

     svn_io_write_atomic2() does a load of magic to allow it to
     replace version files that already exist.  We only need to do
     that when we're allowed to overwrite an existing file. */
  if (! overwrite)
    {
      /* Create the file */
      SVN_ERR(svn_io_file_create(uuid_path, contents->data, scratch_pool));
    }
  else
    {
      SVN_ERR(svn_io_write_atomic2(uuid_path, contents->data, contents->len,
                                   /* perms */
                                   svn_fs_x__path_current(fs, scratch_pool),
                                   ffd->flush_to_disk, scratch_pool));
    }

  fs->uuid = apr_pstrdup(fs->pool, uuid);
  ffd->instance_id = apr_pstrdup(fs->pool, instance_id);

  return SVN_NO_ERROR;
}