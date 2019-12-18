#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; char* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_7__ {char* data; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  copyfrom_rev; void* copyfrom_known; TYPE_1__ path; int /*<<< orphan*/  mergeinfo_mod; void* prop_mod; void* text_mod; int /*<<< orphan*/  change_kind; int /*<<< orphan*/  node_kind; } ;
typedef  TYPE_3__ svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_ADD ; 
 int /*<<< orphan*/  ACTION_DELETE ; 
 int /*<<< orphan*/  ACTION_MODIFY ; 
 int /*<<< orphan*/  ACTION_REPLACE ; 
 void* FALSE ; 
 int /*<<< orphan*/  FLAG_FALSE ; 
 int /*<<< orphan*/  FLAG_TRUE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_FS_X__KIND_DIR ; 
 int /*<<< orphan*/  SVN_FS_X__KIND_FILE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* auto_unescape_path (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_revnum (int /*<<< orphan*/ *,char const**) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_fs_path_change_replace ; 
 int /*<<< orphan*/  svn_fspath__is_canonical (char*) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_2__**,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_tristate_false ; 
 int /*<<< orphan*/  svn_tristate_true ; 

__attribute__((used)) static svn_error_t *
read_change(svn_fs_x__change_t **change_p,
            svn_stream_t *stream,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *line;
  svn_boolean_t eof = TRUE;
  svn_fs_x__change_t *change;
  char *str, *last_str, *kind_str;

  /* Default return value. */
  *change_p = NULL;

  SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, scratch_pool));

  /* Check for a blank line. */
  if (eof || (line->len == 0))
    return SVN_NO_ERROR;

  change = apr_pcalloc(result_pool, sizeof(*change));
  last_str = line->data;

  /* Get the change type. */
  str = svn_cstring_tokenize(" ", &last_str);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  /* Don't bother to check the format number before looking for
   * node-kinds: just read them if you find them. */
  change->node_kind = svn_node_unknown;
  kind_str = strchr(str, '-');
  if (kind_str)
    {
      /* Cap off the end of "str" (the action). */
      *kind_str = '\0';
      kind_str++;
      if (strcmp(kind_str, SVN_FS_X__KIND_FILE) == 0)
        change->node_kind = svn_node_file;
      else if (strcmp(kind_str, SVN_FS_X__KIND_DIR) == 0)
        change->node_kind = svn_node_dir;
      else
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Invalid changes line in rev-file"));
    }

  if (strcmp(str, ACTION_MODIFY) == 0)
    {
      change->change_kind = svn_fs_path_change_modify;
    }
  else if (strcmp(str, ACTION_ADD) == 0)
    {
      change->change_kind = svn_fs_path_change_add;
    }
  else if (strcmp(str, ACTION_DELETE) == 0)
    {
      change->change_kind = svn_fs_path_change_delete;
    }
  else if (strcmp(str, ACTION_REPLACE) == 0)
    {
      change->change_kind = svn_fs_path_change_replace;
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
      change->text_mod = TRUE;
    }
  else if (strcmp(str, FLAG_FALSE) == 0)
    {
      change->text_mod = FALSE;
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
      change->prop_mod = TRUE;
    }
  else if (strcmp(str, FLAG_FALSE) == 0)
    {
      change->prop_mod = FALSE;
    }
  else
    {
      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Invalid prop-mod flag in rev-file"));
    }

  /* Get the mergeinfo-mod flag. */
  str = svn_cstring_tokenize(" ", &last_str);
  if (str == NULL)
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid changes line in rev-file"));

  if (strcmp(str, FLAG_TRUE) == 0)
    {
      change->mergeinfo_mod = svn_tristate_true;
    }
  else if (strcmp(str, FLAG_FALSE) == 0)
    {
      change->mergeinfo_mod = svn_tristate_false;
    }
  else
    {
      return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                              _("Invalid mergeinfo-mod flag in rev-file"));
    }

  /* Get the changed path. */
  if (!svn_fspath__is_canonical(last_str))
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Invalid path in changes line"));

  change->path.data = auto_unescape_path(apr_pstrmemdup(result_pool,
                                                        last_str,
                                                        strlen(last_str)),
                                         result_pool);
  change->path.len = strlen(change->path.data);

  /* Read the next line, the copyfrom line. */
  SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, result_pool));
  change->copyfrom_known = TRUE;
  if (eof || line->len == 0)
    {
      change->copyfrom_rev = SVN_INVALID_REVNUM;
      change->copyfrom_path = NULL;
    }
  else
    {
      last_str = line->data;
      SVN_ERR(parse_revnum(&change->copyfrom_rev, (const char **)&last_str));

      if (!svn_fspath__is_canonical(last_str))
        return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                                _("Invalid copy-from path in changes line"));

      change->copyfrom_path = auto_unescape_path(last_str, result_pool);
    }

  *change_p = change;

  return SVN_NO_ERROR;
}