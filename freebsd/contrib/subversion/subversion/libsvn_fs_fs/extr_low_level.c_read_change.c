#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; char* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyfrom_known; int /*<<< orphan*/  mergeinfo_mod; void* prop_mod; void* text_mod; int /*<<< orphan*/  change_kind; int /*<<< orphan*/  node_kind; int /*<<< orphan*/ * node_rev_id; } ;
typedef  TYPE_3__ svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
struct TYPE_8__ {void* data; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {TYPE_1__ path; TYPE_3__ info; } ;
typedef  TYPE_4__ change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_ADD ; 
 int /*<<< orphan*/  ACTION_DELETE ; 
 int /*<<< orphan*/  ACTION_MODIFY ; 
 int /*<<< orphan*/  ACTION_REPLACE ; 
 int /*<<< orphan*/  ACTION_RESET ; 
 void* FALSE ; 
 int /*<<< orphan*/  FLAG_FALSE ; 
 int /*<<< orphan*/  FLAG_TRUE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_FS__KIND_DIR ; 
 int /*<<< orphan*/  SVN_FS_FS__KIND_FILE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_revnum (int /*<<< orphan*/ *,char const**) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_parse (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_fs_path_change_replace ; 
 int /*<<< orphan*/  svn_fs_path_change_reset ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char*) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_2__**,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_tristate_false ; 
 int /*<<< orphan*/  svn_tristate_true ; 
 int /*<<< orphan*/  svn_tristate_unknown ; 

__attribute__((used)) static svn_error_t *
read_change(change_t **change_p,
            svn_stream_t *stream,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *line;
  svn_boolean_t eof = TRUE;
  change_t *change;
  char *str, *last_str, *kind_str;
  svn_fs_path_change2_t *info;

  /* Default return value. */
  *change_p = NULL;

  SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, scratch_pool));

  /* Check for a blank line. */
  if (eof || (line->len == 0))
    return SVN_NO_ERROR;

  change = apr_pcalloc(result_pool, sizeof(*change));
  info = &change->info;
  last_str = line->data;

  /* Get the node-id of the change. */
  str = svn_cstring_tokenize(" ", &last_str);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  SVN_ERR(svn_fs_fs__id_parse(&info->node_rev_id, str, result_pool));
  if (info->node_rev_id == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  /* Get the change type. */
  str = svn_cstring_tokenize(" ", &last_str);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  /* Don't bother to check the format number before looking for
   * node-kinds: just read them if you find them. */
  info->node_kind = svn_node_unknown;
  kind_str = strchr(str, '-');
  if (kind_str)
    {
      /* Cap off the end of "str" (the action). */
      *kind_str = '\0';
      kind_str++;
      if (strcmp(kind_str, SVN_FS_FS__KIND_FILE) == 0)
        info->node_kind = svn_node_file;
      else if (strcmp(kind_str, SVN_FS_FS__KIND_DIR) == 0)
        info->node_kind = svn_node_dir;
      else
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Invalid changes line in rev-file"));
    }

  if (strcmp(str, ACTION_MODIFY) == 0)
    {
      info->change_kind = svn_fs_path_change_modify;
    }
  else if (strcmp(str, ACTION_ADD) == 0)
    {
      info->change_kind = svn_fs_path_change_add;
    }
  else if (strcmp(str, ACTION_DELETE) == 0)
    {
      info->change_kind = svn_fs_path_change_delete;
    }
  else if (strcmp(str, ACTION_REPLACE) == 0)
    {
      info->change_kind = svn_fs_path_change_replace;
    }
  else if (strcmp(str, ACTION_RESET) == 0)
    {
      info->change_kind = svn_fs_path_change_reset;
    }
  else
    {
      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Invalid change kind in rev file"));
    }

  /* Get the text-mod flag. */
  str = svn_cstring_tokenize(" ", &last_str);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  if (strcmp(str, FLAG_TRUE) == 0)
    {
      info->text_mod = TRUE;
    }
  else if (strcmp(str, FLAG_FALSE) == 0)
    {
      info->text_mod = FALSE;
    }
  else
    {
      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Invalid text-mod flag in rev-file"));
    }

  /* Get the prop-mod flag. */
  str = svn_cstring_tokenize(" ", &last_str);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  if (strcmp(str, FLAG_TRUE) == 0)
    {
      info->prop_mod = TRUE;
    }
  else if (strcmp(str, FLAG_FALSE) == 0)
    {
      info->prop_mod = FALSE;
    }
  else
    {
      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Invalid prop-mod flag in rev-file"));
    }

  /* Get the mergeinfo-mod flag if given.  Otherwise, the next thing
     is the path starting with a slash.  Also, we must initialize the
     flag explicitly because 0 is not valid for a svn_tristate_t. */
  info->mergeinfo_mod = svn_tristate_unknown;
  if (*last_str != '/')
    {
      str = svn_cstring_tokenize(" ", &last_str);
      if (str == NULL)
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Invalid changes line in rev-file"));

      if (strcmp(str, FLAG_TRUE) == 0)
        {
          info->mergeinfo_mod = svn_tristate_true;
        }
      else if (strcmp(str, FLAG_FALSE) == 0)
        {
          info->mergeinfo_mod = svn_tristate_false;
        }
      else
        {
          return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Invalid mergeinfo-mod flag in rev-file"));
        }
    }

  /* Get the changed path. */
  if (!svn_fspath__is_canonical(last_str))
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid path in changes line"));

  change->path.len = strlen(last_str);
  change->path.data = apr_pstrdup(result_pool, last_str);

  /* Read the next line, the copyfrom line. */
  SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, scratch_pool));
  info->copyfrom_known = TRUE;
  if (eof || line->len == 0)
    {
      info->copyfrom_rev = SVN_INVALID_REVNUM;
      info->copyfrom_path = NULL;
    }
  else
    {
      last_str = line->data;
      SVN_ERR(parse_revnum(&info->copyfrom_rev, (const char **)&last_str));

      if (!svn_fspath__is_canonical(last_str))
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Invalid copy-from path in changes line"));

      info->copyfrom_path = apr_pstrdup(result_pool, last_str);
    }

  *change_p = change;

  return SVN_NO_ERROR;
}