#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_30__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_t ;
struct TYPE_31__ {void* show_c_function; void* ignore_eol_style; int /*<<< orphan*/  ignore_space; } ;
typedef  TYPE_3__ svn_diff_file_options_t ;
typedef  int /*<<< orphan*/  svn_diff_conflict_display_style_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 TYPE_1__* generate_conflict_message (char const*,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_conflict_display_modified_original_latest ; 
 scalar_t__ svn_diff_contains_conflicts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_file_ignore_space_none ; 
 TYPE_3__* svn_diff_file_options_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_mem_string_diff3 (int /*<<< orphan*/ **,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_mem_string_output_merge3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_2__*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_io_is_binary_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_string_create_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_string_create_from_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  svn_utf_cstring_from_utf8_fuzzy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
prop_conflict_new(const svn_string_t **conflict_desc,
                  const char *propname,
                  const svn_string_t *original,
                  const svn_string_t *mine,
                  const svn_string_t *incoming,
                  const svn_string_t *incoming_base,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_diff_t *diff;
  svn_diff_file_options_t *diff_opts;
  svn_stringbuf_t *buf;
  svn_boolean_t incoming_base_is_binary;
  svn_boolean_t mine_is_binary;
  svn_boolean_t incoming_is_binary;

  buf = generate_conflict_message(propname, original, mine, incoming,
                                  incoming_base, scratch_pool);

  /* Convert deleted or not-yet-added values to empty-string values, for the
     purposes of diff generation and binary detection. */
  if (mine == NULL)
    mine = svn_string_create_empty(scratch_pool);
  if (incoming == NULL)
    incoming = svn_string_create_empty(scratch_pool);
  if (incoming_base == NULL)
    incoming_base = svn_string_create_empty(scratch_pool);

  /* How we render the conflict:

     We have four sides: original, mine, incoming_base, incoming.
     We render the conflict as a 3-way diff.  A diff3 API has three parts,
     called:

       <<< - original
       ||| - modified (or "older")
       === - latest (or "theirs")
       >>>

     We fill those parts as follows:

       PART      FILLED BY SKEL MEMBER  USER-FACING ROLE
       ====      =====================  ================
       original  mine                   was WORKING tree at conflict creation
       modified  incoming_base          left-hand side of merge
       latest    incoming               right-hand side of merge
       (none)    original               was BASE tree at conflict creation

     An 'update -r rN' is treated like a 'merge -r BASE:rN', i.e., in an
     'update' operation skel->original and skel->incoming_base coincide.

     Note that the term "original" is used both in the skel and in diff3
     with different meanings.  Note also that the skel's ORIGINAL value was
     at some point in the BASE tree, but the BASE tree need not have contained
     the INCOMING_BASE value.

     Yes, it's confusing. */

  /* If any of the property values involved in the diff is binary data,
   * do not generate a diff. */
  incoming_base_is_binary = svn_io_is_binary_data(incoming_base->data,
                                                  incoming_base->len);
  mine_is_binary = svn_io_is_binary_data(mine->data, mine->len);
  incoming_is_binary = svn_io_is_binary_data(incoming->data, incoming->len);

  if (!(incoming_base_is_binary || mine_is_binary || incoming_is_binary))
    {
      diff_opts = svn_diff_file_options_create(scratch_pool);
      diff_opts->ignore_space = svn_diff_file_ignore_space_none;
      diff_opts->ignore_eol_style = FALSE;
      diff_opts->show_c_function = FALSE;
      /* Pass skel member INCOMING_BASE into the formal parameter ORIGINAL.
         Ignore the skel member ORIGINAL. */
      SVN_ERR(svn_diff_mem_string_diff3(&diff, incoming_base, mine, incoming,
                                        diff_opts, scratch_pool));
      if (svn_diff_contains_conflicts(diff))
        {
          svn_stream_t *stream;
          svn_diff_conflict_display_style_t style;
          const char *mine_marker = _("<<<<<<< (local property value)");
          const char *incoming_marker = _(">>>>>>> (incoming 'changed to' value)");
          const char *incoming_base_marker = _("||||||| (incoming 'changed from' value)");
          const char *separator = "=======";
          svn_string_t *incoming_base_ascii =
            svn_string_create(svn_utf_cstring_from_utf8_fuzzy(incoming_base->data,
                                                              scratch_pool),
                              scratch_pool);
          svn_string_t *mine_ascii =
            svn_string_create(svn_utf_cstring_from_utf8_fuzzy(mine->data,
                                                              scratch_pool),
                              scratch_pool);
          svn_string_t *incoming_ascii =
            svn_string_create(svn_utf_cstring_from_utf8_fuzzy(incoming->data,
                                                              scratch_pool),
                              scratch_pool);

          style = svn_diff_conflict_display_modified_original_latest;
          stream = svn_stream_from_stringbuf(buf, scratch_pool);
          SVN_ERR(svn_stream_skip(stream, buf->len));
          SVN_ERR(svn_diff_mem_string_output_merge3(stream, diff,
                                                    incoming_base_ascii,
                                                    mine_ascii,
                                                    incoming_ascii,
                                                    incoming_base_marker, mine_marker,
                                                    incoming_marker, separator,
                                                    style,
                                                    cancel_func, cancel_baton,
                                                    scratch_pool));
          SVN_ERR(svn_stream_close(stream));

          *conflict_desc = svn_string_create_from_buf(buf, result_pool);
          return SVN_NO_ERROR;
        }
    }

  /* If we could not print a conflict diff just print full values . */
  if (mine->len > 0)
    {
      svn_stringbuf_appendcstr(buf, _("Local property value:\n"));
      if (mine_is_binary)
        svn_stringbuf_appendcstr(buf, _("Cannot display: property value is "
                                        "binary data\n"));
      else
        svn_stringbuf_appendbytes(buf, mine->data, mine->len);
      svn_stringbuf_appendcstr(buf, "\n");
    }

  if (incoming->len > 0)
    {
      svn_stringbuf_appendcstr(buf, _("Incoming property value:\n"));
      if (incoming_is_binary)
        svn_stringbuf_appendcstr(buf, _("Cannot display: property value is "
                                        "binary data\n"));
      else
        svn_stringbuf_appendbytes(buf, incoming->data, incoming->len);
      svn_stringbuf_appendcstr(buf, "\n");
    }

  *conflict_desc = svn_string_create_from_buf(buf, result_pool);
  return SVN_NO_ERROR;
}