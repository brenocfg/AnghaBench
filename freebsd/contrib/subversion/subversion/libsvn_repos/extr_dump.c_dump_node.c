#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos__dumpfile_headers_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
struct TYPE_13__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  void* svn_boolean_t ;
struct edit_baton {int current_rev; int oldest_dumped_rev; int /*<<< orphan*/  stream; int /*<<< orphan*/ * fs_root; scalar_t__ use_deltas; int /*<<< orphan*/  notify_baton; scalar_t__ notify_func; scalar_t__ check_normalization; scalar_t__ verify; int /*<<< orphan*/  found_old_mergeinfo; void** found_old_reference; int /*<<< orphan*/  path_tracker; } ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  enum svn_node_action { ____Placeholder_svn_node_action } svn_node_action ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ ARE_VALID_COPY_ARGS (char const*,int) ; 
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_ACTION ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_COPYFROM_PATH ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_KIND ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_NODE_PATH ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_PROP_DELTA ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_CONTENT_MD5 ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_CONTENT_SHA1 ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_COPY_SOURCE_MD5 ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_COPY_SOURCE_SHA1 ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_DELTA ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_DELTA_BASE_MD5 ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_TEXT_DELTA_BASE_SHA1 ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  check_mergeinfo_normalization (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_node_delete (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_must_exist (struct edit_baton*,char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_must_not_exist (struct edit_baton*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_warning (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  store_delta (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_err_best_message (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_fs__path_valid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_contents_changed (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_props_changed (void**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_write_incremental (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
#define  svn_node_action_add 131 
#define  svn_node_action_change 130 
#define  svn_node_action_delete 129 
#define  svn_node_action_replace 128 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_unknown ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dump_headers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dump_node_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_pushf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * svn_repos__dumpfile_headers_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_notify_warning_found_old_reference ; 
 int /*<<< orphan*/  svn_repos_notify_warning_invalid_fspath ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_disown (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_write (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_ensure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracker_path_add (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracker_path_copy (int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int /*<<< orphan*/  tracker_path_delete (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tracker_path_replace (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* verify_mergeinfo_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
dump_node(struct edit_baton *eb,
          const char *path,
          svn_node_kind_t kind,
          enum svn_node_action action,
          svn_boolean_t is_copy,
          const char *cmp_path,
          svn_revnum_t cmp_rev,
          apr_pool_t *pool)
{
  svn_stringbuf_t *propstring;
  apr_size_t len;
  svn_boolean_t must_dump_text = FALSE, must_dump_props = FALSE;
  const char *compare_path = path;
  svn_revnum_t compare_rev = eb->current_rev - 1;
  svn_fs_root_t *compare_root = NULL;
  apr_file_t *delta_file = NULL;
  svn_repos__dumpfile_headers_t *headers
    = svn_repos__dumpfile_headers_create(pool);
  svn_filesize_t textlen;

  /* Maybe validate the path. */
  if (eb->verify || eb->notify_func)
    {
      svn_error_t *err = svn_fs__path_valid(path, pool);

      if (err)
        {
          if (eb->notify_func)
            {
              char errbuf[512]; /* ### svn_strerror() magic number  */

              notify_warning(pool, eb->notify_func, eb->notify_baton,
                             svn_repos_notify_warning_invalid_fspath,
                             _("E%06d: While validating fspath '%s': %s"),
                             err->apr_err, path,
                             svn_err_best_message(err, errbuf, sizeof(errbuf)));
            }

          /* Return the error in addition to notifying about it. */
          if (eb->verify)
            return svn_error_trace(err);
          else
            svn_error_clear(err);
        }
    }

  /* Write out metadata headers for this file node. */
  svn_repos__dumpfile_header_push(
    headers, SVN_REPOS_DUMPFILE_NODE_PATH, path);
  if (kind == svn_node_file)
    svn_repos__dumpfile_header_push(
      headers, SVN_REPOS_DUMPFILE_NODE_KIND, "file");
  else if (kind == svn_node_dir)
    svn_repos__dumpfile_header_push(
      headers, SVN_REPOS_DUMPFILE_NODE_KIND, "dir");

  /* Remove leading slashes from copyfrom paths. */
  if (cmp_path)
    cmp_path = svn_relpath_canonicalize(cmp_path, pool);

  /* Validate the comparison path/rev. */
  if (ARE_VALID_COPY_ARGS(cmp_path, cmp_rev))
    {
      compare_path = cmp_path;
      compare_rev = cmp_rev;
    }

  switch (action)
    {
    case svn_node_action_change:
      if (eb->path_tracker)
        SVN_ERR_W(node_must_exist(eb, path, eb->current_rev, kind, pool),
                  apr_psprintf(pool, _("Change invalid path '%s' in r%ld"),
                               path, eb->current_rev));

      svn_repos__dumpfile_header_push(
        headers, SVN_REPOS_DUMPFILE_NODE_ACTION, "change");

      /* either the text or props changed, or possibly both. */
      SVN_ERR(svn_fs_revision_root(&compare_root,
                                   svn_fs_root_fs(eb->fs_root),
                                   compare_rev, pool));

      SVN_ERR(svn_fs_props_changed(&must_dump_props,
                                   compare_root, compare_path,
                                   eb->fs_root, path, pool));
      if (kind == svn_node_file)
        SVN_ERR(svn_fs_contents_changed(&must_dump_text,
                                        compare_root, compare_path,
                                        eb->fs_root, path, pool));
      break;

    case svn_node_action_delete:
      if (eb->path_tracker)
        {
          SVN_ERR_W(node_must_exist(eb, path, eb->current_rev, kind, pool),
                    apr_psprintf(pool, _("Deleting invalid path '%s' in r%ld"),
                                 path, eb->current_rev));
          tracker_path_delete(eb->path_tracker, path);
        }

      svn_repos__dumpfile_header_push(
        headers, SVN_REPOS_DUMPFILE_NODE_ACTION, "delete");

      /* we can leave this routine quietly now, don't need to dump
         any content. */
      must_dump_text = FALSE;
      must_dump_props = FALSE;
      break;

    case svn_node_action_replace:
      if (eb->path_tracker)
        SVN_ERR_W(node_must_exist(eb, path, eb->current_rev,
                                  svn_node_unknown, pool),
                  apr_psprintf(pool,
                               _("Replacing non-existent path '%s' in r%ld"),
                               path, eb->current_rev));

      if (! is_copy)
        {
          if (eb->path_tracker)
            tracker_path_replace(eb->path_tracker, path);

          /* a simple delete+add, implied by a single 'replace' action. */
          svn_repos__dumpfile_header_push(
            headers, SVN_REPOS_DUMPFILE_NODE_ACTION, "replace");

          /* definitely need to dump all content for a replace. */
          if (kind == svn_node_file)
            must_dump_text = TRUE;
          must_dump_props = TRUE;
          break;
        }
      else
        {
          /* more complex:  delete original, then add-with-history.  */
          /* ### Why not write a 'replace' record? Don't know. */

          if (eb->path_tracker)
            {
              tracker_path_delete(eb->path_tracker, path);
            }

          /* ### Unusually, we end this 'delete' node record with only a single
                 blank line after the header block -- no extra blank line. */
          SVN_ERR(dump_node_delete(eb->stream, path, pool));

          /* The remaining action is a non-replacing add-with-history */
          /* action = svn_node_action_add; */
        }
      /* FALL THROUGH to 'add' */

    case svn_node_action_add:
      if (eb->path_tracker)
        SVN_ERR_W(node_must_not_exist(eb, path, eb->current_rev, pool),
                  apr_psprintf(pool,
                               _("Adding already existing path '%s' in r%ld"),
                               path, eb->current_rev));

      svn_repos__dumpfile_header_push(
        headers, SVN_REPOS_DUMPFILE_NODE_ACTION, "add");

      if (! is_copy)
        {
          if (eb->path_tracker)
            tracker_path_add(eb->path_tracker, path);

          /* Dump all contents for a simple 'add'. */
          if (kind == svn_node_file)
            must_dump_text = TRUE;
          must_dump_props = TRUE;
        }
      else
        {
          if (eb->path_tracker)
            {
              SVN_ERR_W(node_must_exist(eb, compare_path, compare_rev,
                                        kind, pool),
                        apr_psprintf(pool,
                                     _("Copying from invalid path to "
                                       "'%s' in r%ld"),
                                     path, eb->current_rev));
              tracker_path_copy(eb->path_tracker, path, compare_path,
                                compare_rev);
            }

          if (!eb->verify && cmp_rev < eb->oldest_dumped_rev
              && eb->notify_func)
            {
              notify_warning(pool, eb->notify_func, eb->notify_baton,
                             svn_repos_notify_warning_found_old_reference,
                             _("Referencing data in revision %ld,"
                               " which is older than the oldest"
                               " dumped revision (r%ld).  Loading this dump"
                               " into an empty repository"
                               " will fail."),
                             cmp_rev, eb->oldest_dumped_rev);
              if (eb->found_old_reference)
                *eb->found_old_reference = TRUE;
            }

          svn_repos__dumpfile_header_pushf(
            headers, SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV, "%ld", cmp_rev);
          svn_repos__dumpfile_header_push(
            headers, SVN_REPOS_DUMPFILE_NODE_COPYFROM_PATH, cmp_path);

          SVN_ERR(svn_fs_revision_root(&compare_root,
                                       svn_fs_root_fs(eb->fs_root),
                                       compare_rev, pool));

          /* Need to decide if the copied node had any extra textual or
             property mods as well.  */
          SVN_ERR(svn_fs_props_changed(&must_dump_props,
                                       compare_root, compare_path,
                                       eb->fs_root, path, pool));
          if (kind == svn_node_file)
            {
              svn_checksum_t *checksum;
              const char *hex_digest;
              SVN_ERR(svn_fs_contents_changed(&must_dump_text,
                                              compare_root, compare_path,
                                              eb->fs_root, path, pool));

              SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5,
                                           compare_root, compare_path,
                                           FALSE, pool));
              hex_digest = svn_checksum_to_cstring(checksum, pool);
              if (hex_digest)
                svn_repos__dumpfile_header_push(
                  headers, SVN_REPOS_DUMPFILE_TEXT_COPY_SOURCE_MD5, hex_digest);

              SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_sha1,
                                           compare_root, compare_path,
                                           FALSE, pool));
              hex_digest = svn_checksum_to_cstring(checksum, pool);
              if (hex_digest)
                svn_repos__dumpfile_header_push(
                  headers, SVN_REPOS_DUMPFILE_TEXT_COPY_SOURCE_SHA1, hex_digest);
            }
        }
      break;
    }

  if ((! must_dump_text) && (! must_dump_props))
    {
      /* If we're not supposed to dump text or props, so be it, we can
         just go home.  However, if either one needs to be dumped,
         then our dumpstream format demands that at a *minimum*, we
         see a lone "PROPS-END" as a divider between text and props
         content within the content-block. */
      SVN_ERR(svn_repos__dump_headers(eb->stream, headers, pool));
      len = 1;
      return svn_stream_write(eb->stream, "\n", &len); /* ### needed? */
    }

  /*** Start prepping content to dump... ***/

  /* If we are supposed to dump properties, write out a property
     length header and generate a stringbuf that contains those
     property values here. */
  if (must_dump_props)
    {
      apr_hash_t *prophash, *oldhash = NULL;
      svn_stream_t *propstream;

      SVN_ERR(svn_fs_node_proplist(&prophash, eb->fs_root, path, pool));

      /* If this is a partial dump, then issue a warning if we dump mergeinfo
         properties that refer to revisions older than the first revision
         dumped. */
      if (!eb->verify && eb->notify_func && eb->oldest_dumped_rev > 1)
        {
          svn_string_t *mergeinfo_str = svn_hash_gets(prophash,
                                                      SVN_PROP_MERGEINFO);
          if (mergeinfo_str)
            {
              /* An error in verifying the mergeinfo must not prevent dumping
                 the data. Ignore any such error. */
              svn_error_clear(verify_mergeinfo_revisions(
                                eb->found_old_mergeinfo,
                                mergeinfo_str->data, eb->oldest_dumped_rev,
                                eb->notify_func, eb->notify_baton,
                                pool));
            }
        }

      /* If we're checking UCS normalization, also parse any changed
         mergeinfo and warn about denormalized paths and name
         collisions there. */
      if (eb->verify && eb->check_normalization && eb->notify_func)
        {
          /* N.B.: This hash lookup happens only once; the conditions
             for verifying historic mergeinfo references and checking
             UCS normalization are mutually exclusive. */
          svn_string_t *mergeinfo_str = svn_hash_gets(prophash,
                                                      SVN_PROP_MERGEINFO);
          if (mergeinfo_str)
            {
              svn_string_t *oldinfo_str = NULL;
              if (compare_root)
                {
                  SVN_ERR(svn_fs_node_proplist(&oldhash,
                                               compare_root, compare_path,
                                               pool));
                  oldinfo_str = svn_hash_gets(oldhash, SVN_PROP_MERGEINFO);
                }
              SVN_ERR(check_mergeinfo_normalization(
                          path, mergeinfo_str->data,
                          (oldinfo_str ? oldinfo_str->data : NULL),
                          eb->notify_func, eb->notify_baton, pool));
            }
        }

      if (eb->use_deltas && compare_root)
        {
          /* Fetch the old property hash to diff against and output a header
             saying that our property contents are a delta. */
          if (!oldhash)         /* May have been set for normalization check */
            SVN_ERR(svn_fs_node_proplist(&oldhash, compare_root, compare_path,
                                         pool));
          svn_repos__dumpfile_header_push(
            headers, SVN_REPOS_DUMPFILE_PROP_DELTA, "true");
        }
      else
        oldhash = apr_hash_make(pool);
      propstring = svn_stringbuf_create_ensure(0, pool);
      propstream = svn_stream_from_stringbuf(propstring, pool);
      SVN_ERR(svn_hash_write_incremental(prophash, oldhash, propstream,
                                         "PROPS-END", pool));
      SVN_ERR(svn_stream_close(propstream));
    }

  /* If we are supposed to dump text, write out a text length header
     here, and an MD5 checksum (if available). */
  if (must_dump_text && (kind == svn_node_file))
    {
      svn_checksum_t *checksum;
      const char *hex_digest;

      if (eb->use_deltas)
        {
          /* Compute the text delta now and write it into a temporary
             file, so that we can find its length.  Output a header
             saying our text contents are a delta. */
          SVN_ERR(store_delta(&delta_file, &textlen, compare_root,
                              compare_path, eb->fs_root, path, pool));
          svn_repos__dumpfile_header_push(
            headers, SVN_REPOS_DUMPFILE_TEXT_DELTA, "true");

          if (compare_root)
            {
              SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5,
                                           compare_root, compare_path,
                                           FALSE, pool));
              hex_digest = svn_checksum_to_cstring(checksum, pool);
              if (hex_digest)
                svn_repos__dumpfile_header_push(
                  headers, SVN_REPOS_DUMPFILE_TEXT_DELTA_BASE_MD5, hex_digest);

              SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_sha1,
                                           compare_root, compare_path,
                                           FALSE, pool));
              hex_digest = svn_checksum_to_cstring(checksum, pool);
              if (hex_digest)
                svn_repos__dumpfile_header_push(
                  headers, SVN_REPOS_DUMPFILE_TEXT_DELTA_BASE_SHA1, hex_digest);
            }
        }
      else
        {
          /* Just fetch the length of the file. */
          SVN_ERR(svn_fs_file_length(&textlen, eb->fs_root, path, pool));
        }

      SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5,
                                   eb->fs_root, path, FALSE, pool));
      hex_digest = svn_checksum_to_cstring(checksum, pool);
      if (hex_digest)
        svn_repos__dumpfile_header_push(
          headers, SVN_REPOS_DUMPFILE_TEXT_CONTENT_MD5, hex_digest);

      SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_sha1,
                                   eb->fs_root, path, FALSE, pool));
      hex_digest = svn_checksum_to_cstring(checksum, pool);
      if (hex_digest)
        svn_repos__dumpfile_header_push(
          headers, SVN_REPOS_DUMPFILE_TEXT_CONTENT_SHA1, hex_digest);
    }

  /* 'Content-length:' is the last header before we dump the content,
     and is the sum of the text and prop contents lengths.  We write
     this only for the benefit of non-Subversion RFC-822 parsers. */
  SVN_ERR(svn_repos__dump_node_record(eb->stream, headers,
                                      must_dump_props ? propstring : NULL,
                                      must_dump_text,
                                      must_dump_text ? textlen : 0,
                                      TRUE /*content_length_always*/,
                                      pool));

  /* Dump text content */
  if (must_dump_text && (kind == svn_node_file))
    {
      svn_stream_t *contents;

      if (delta_file)
        {
          /* Make sure to close the underlying file when the stream is
             closed. */
          contents = svn_stream_from_aprfile2(delta_file, FALSE, pool);
        }
      else
        SVN_ERR(svn_fs_file_contents(&contents, eb->fs_root, path, pool));

      SVN_ERR(svn_stream_copy3(contents, svn_stream_disown(eb->stream, pool),
                               NULL, NULL, pool));
    }

  len = 2;
  return svn_stream_write(eb->stream, "\n\n", &len); /* ### needed? */
}