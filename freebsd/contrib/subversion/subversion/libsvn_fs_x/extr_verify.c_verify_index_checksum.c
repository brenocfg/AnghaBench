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
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_3__ {int end; int start; int /*<<< orphan*/  checksum; } ;
typedef  TYPE_1__ svn_fs_x__index_info_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  (* svn_cancel_func_t ) (void*) ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__STREAM_CHUNK_SIZE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_mismatch_err (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_name (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
verify_index_checksum(svn_fs_x__revision_file_t *file,
                      const char *name,
                      svn_fs_x__index_info_t *index_info,
                      svn_cancel_func_t cancel_func,
                      void *cancel_baton,
                      apr_pool_t *scratch_pool)
{
  unsigned char buffer[SVN__STREAM_CHUNK_SIZE];
  apr_off_t size = index_info->end - index_info->start;
  svn_checksum_t *actual;
  svn_checksum_ctx_t *context
    = svn_checksum_ctx_create(svn_checksum_md5, scratch_pool);

  /* Calculate the index checksum. */
  SVN_ERR(svn_fs_x__rev_file_seek(file, NULL, index_info->start));
  while (size > 0)
    {
      apr_size_t to_read = size > sizeof(buffer)
                         ? sizeof(buffer)
                         : (apr_size_t)size;
      SVN_ERR(svn_fs_x__rev_file_read(file, buffer, to_read));
      SVN_ERR(svn_checksum_update(context, buffer, to_read));
      size -= to_read;

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));
    }

  SVN_ERR(svn_checksum_final(&actual, context, scratch_pool));

  /* Verify that it matches the expected checksum. */
  if (!svn_checksum_match(index_info->checksum, actual))
    {
      const char *file_name;

      SVN_ERR(svn_fs_x__rev_file_name(&file_name, file, scratch_pool));
      SVN_ERR(svn_checksum_mismatch_err(index_info->checksum, actual,
                                        scratch_pool, 
                                        _("%s checksum mismatch in file %s"),
                                        name, file_name));
    }

  return SVN_NO_ERROR;
}