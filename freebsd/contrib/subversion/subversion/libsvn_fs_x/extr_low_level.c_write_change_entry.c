#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int change_kind; scalar_t__ node_kind; scalar_t__ mergeinfo_mod; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  copyfrom_rev; TYPE_1__ path; scalar_t__ prop_mod; scalar_t__ text_mod; } ;
typedef  TYPE_3__ svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* ACTION_ADD ; 
 char* ACTION_DELETE ; 
 char* ACTION_MODIFY ; 
 char* ACTION_REPLACE ; 
 int /*<<< orphan*/  FLAG_FALSE ; 
 int /*<<< orphan*/  FLAG_TRUE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_X__KIND_DIR ; 
 int /*<<< orphan*/  SVN_FS_X__KIND_FILE ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  auto_escape_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
#define  svn_fs_path_change_add 131 
#define  svn_fs_path_change_delete 130 
#define  svn_fs_path_change_modify 129 
#define  svn_fs_path_change_replace 128 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_2__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_2__*,char*) ; 
 TYPE_2__* svn_stringbuf_createf (int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_tristate_true ; 

__attribute__((used)) static svn_error_t *
write_change_entry(svn_stream_t *stream,
                   svn_fs_x__change_t *change,
                   apr_pool_t *scratch_pool)
{
  const char *change_string = NULL;
  const char *kind_string = "";
  svn_stringbuf_t *buf;
  apr_size_t len;

  switch (change->change_kind)
    {
    case svn_fs_path_change_modify:
      change_string = ACTION_MODIFY;
      break;
    case svn_fs_path_change_add:
      change_string = ACTION_ADD;
      break;
    case svn_fs_path_change_delete:
      change_string = ACTION_DELETE;
      break;
    case svn_fs_path_change_replace:
      change_string = ACTION_REPLACE;
      break;
    default:
      return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                               _("Invalid change type %d"),
                               change->change_kind);
    }

  SVN_ERR_ASSERT(change->node_kind == svn_node_dir
                 || change->node_kind == svn_node_file);
  kind_string = apr_psprintf(scratch_pool, "-%s",
                             change->node_kind == svn_node_dir
                             ? SVN_FS_X__KIND_DIR
                             : SVN_FS_X__KIND_FILE);

  buf = svn_stringbuf_createf(scratch_pool, "%s%s %s %s %s %s\n",
                              change_string, kind_string,
                              change->text_mod ? FLAG_TRUE : FLAG_FALSE,
                              change->prop_mod ? FLAG_TRUE : FLAG_FALSE,
                              change->mergeinfo_mod == svn_tristate_true
                                               ? FLAG_TRUE : FLAG_FALSE,
                              auto_escape_path(change->path.data, scratch_pool));

  if (SVN_IS_VALID_REVNUM(change->copyfrom_rev))
    {
      svn_stringbuf_appendcstr(buf, apr_psprintf(scratch_pool, "%ld %s",
                               change->copyfrom_rev,
                               auto_escape_path(change->copyfrom_path,
                                                scratch_pool)));
    }

  svn_stringbuf_appendbyte(buf, '\n');

  /* Write all change info in one write call. */
  len = buf->len;
  return svn_error_trace(svn_stream_write(stream, buf->data, &len));
}