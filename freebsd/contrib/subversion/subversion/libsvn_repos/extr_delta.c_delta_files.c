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
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct context {int /*<<< orphan*/ * source_root; int /*<<< orphan*/  target_root; scalar_t__ text_deltas; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  delta_proplists (struct context*,char const*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_text_delta (struct context*,void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 char* svn_checksum_to_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_contents_different (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_get_file_delta_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delta_files(struct context *c,
            void *file_baton,
            const char *source_path,
            const char *target_path,
            apr_pool_t *pool)
{
  apr_pool_t *subpool;
  svn_boolean_t changed = TRUE;

  SVN_ERR_ASSERT(target_path);

  /* Make a subpool for local allocations. */
  subpool = svn_pool_create(pool);

  /* Compare the files' property lists.  */
  SVN_ERR(delta_proplists(c, source_path, target_path,
                          change_file_prop, file_baton, subpool));

  if (source_path)
    {
      SVN_ERR(svn_fs_contents_different(&changed,
                                        c->target_root, target_path,
                                        c->source_root, source_path,
                                        subpool));
    }
  else
    {
      /* If there isn't a source path, this is an add, which
         necessarily has textual mods. */
    }

  /* If there is a change, and the context indicates that we should
     care about it, then hand it off to a delta stream.  */
  if (changed)
    {
      svn_txdelta_stream_t *delta_stream = NULL;
      svn_checksum_t *source_checksum;
      const char *source_hex_digest = NULL;

      if (c->text_deltas)
        {
          /* Get a delta stream turning an empty file into one having
             TARGET_PATH's contents.  */
          SVN_ERR(svn_fs_get_file_delta_stream
                  (&delta_stream,
                   source_path ? c->source_root : NULL,
                   source_path ? source_path : NULL,
                   c->target_root, target_path, subpool));
        }

      if (source_path)
        {
          SVN_ERR(svn_fs_file_checksum(&source_checksum, svn_checksum_md5,
                                       c->source_root, source_path, TRUE,
                                       subpool));

          source_hex_digest = svn_checksum_to_cstring(source_checksum,
                                                      subpool);
        }

      SVN_ERR(send_text_delta(c, file_baton, source_hex_digest,
                              delta_stream, subpool));
    }

  /* Cleanup. */
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}