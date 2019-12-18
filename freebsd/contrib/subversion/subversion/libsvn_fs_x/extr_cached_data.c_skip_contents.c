#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  revision; } ;
struct TYPE_7__ {int /*<<< orphan*/  off; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/  scratch_pool; TYPE_3__* current_fulltext; int /*<<< orphan*/  filehandle_pool; int /*<<< orphan*/  len; TYPE_1__ fulltext_cache_key; } ;
typedef  TYPE_2__ rep_read_baton_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {scalar_t__ len; char* data; } ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__STREAM_CHUNK_SIZE ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * get_contents_from_windows (TYPE_2__*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  optimimal_allocation_size (scalar_t__) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_stringbuf_create_ensure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
skip_contents(rep_read_baton_t *baton,
              svn_filesize_t len)
{
  svn_error_t *err = SVN_NO_ERROR;

  /* Do we want to cache the reconstructed fulltext? */
  if (SVN_IS_VALID_REVNUM(baton->fulltext_cache_key.revision))
    {
      char *buffer;
      svn_filesize_t to_alloc = MAX(len, baton->len);

      /* This should only be happening if BATON->LEN and LEN are
       * cacheable, implying they fit into memory. */
      SVN_ERR_ASSERT((apr_size_t)to_alloc == to_alloc);

      /* Allocate the fulltext buffer. */
      baton->current_fulltext = svn_stringbuf_create_ensure(
                        optimimal_allocation_size((apr_size_t)to_alloc),
                        baton->filehandle_pool);

      /* Read LEN bytes from the window stream and store the data
       * in the fulltext buffer (will be filled by further reads later). */
      baton->current_fulltext->len = (apr_size_t)len;
      baton->current_fulltext->data[(apr_size_t)len] = 0;

      buffer = baton->current_fulltext->data;
      while (len > 0 && !err)
        {
          apr_size_t to_read = (apr_size_t)len;
          err = get_contents_from_windows(baton, buffer, &to_read);
          len -= to_read;
          buffer += to_read;
        }

      /* Make the MD5 calculation catch up with the data delivered
       * (we did not run MD5 on the data that we took from the cache). */
      if (!err)
        {
          SVN_ERR(svn_checksum_update(baton->md5_checksum_ctx,
                                      baton->current_fulltext->data,
                                      baton->current_fulltext->len));
          baton->off += baton->current_fulltext->len;
        }
    }
  else if (len > 0)
    {
      /* Simply drain LEN bytes from the window stream. */
      apr_pool_t *subpool = svn_pool_create(baton->scratch_pool);
      char *buffer = apr_palloc(subpool, SVN__STREAM_CHUNK_SIZE);

      while (len > 0 && !err)
        {
          apr_size_t to_read = len > SVN__STREAM_CHUNK_SIZE
                            ? SVN__STREAM_CHUNK_SIZE
                            : (apr_size_t)len;

          err = get_contents_from_windows(baton, buffer, &to_read);
          len -= to_read;

          /* Make the MD5 calculation catch up with the data delivered
           * (we did not run MD5 on the data that we took from the cache). */
          if (!err)
            {
              SVN_ERR(svn_checksum_update(baton->md5_checksum_ctx,
                                          buffer, to_read));
              baton->off += to_read;
            }
        }

      svn_pool_destroy(subpool);
    }

  return svn_error_trace(err);
}