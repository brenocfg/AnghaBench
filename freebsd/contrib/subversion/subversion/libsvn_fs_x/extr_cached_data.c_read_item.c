#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t len; scalar_t__* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_7__ {size_t size; scalar_t__ fnv1_checksum; size_t offset; } ;
typedef  TYPE_2__ svn_fs_x__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_off_t_toa (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ htonl (scalar_t__) ; 
 scalar_t__ svn__fnv1a_32x4 (scalar_t__*,size_t) ; 
 int /*<<< orphan*/ * svn_checksum__from_digest_fnv1a_32x4 (unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_read (int /*<<< orphan*/ *,scalar_t__*,size_t) ; 
 int /*<<< orphan*/ * svn_stream_from_stringbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create_ensure (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_item(svn_stream_t **stream,
          svn_fs_t *fs,
          svn_fs_x__revision_file_t *rev_file,
          svn_fs_x__p2l_entry_t* entry,
          apr_pool_t *result_pool)
{
  apr_uint32_t digest;
  svn_checksum_t *expected, *actual;
  apr_uint32_t plain_digest;
  svn_stringbuf_t *text;

  /* Read item into string buffer. */
  text = svn_stringbuf_create_ensure(entry->size, result_pool);
  text->len = entry->size;
  text->data[text->len] = 0;
  SVN_ERR(svn_fs_x__rev_file_read(rev_file, text->data, text->len));

  /* Return (construct, calculate) stream and checksum. */
  *stream = svn_stream_from_stringbuf(text, result_pool);
  digest = svn__fnv1a_32x4(text->data, text->len);

  /* Checksums will match most of the time. */
  if (entry->fnv1_checksum == digest)
    return SVN_NO_ERROR;

  /* Construct proper checksum objects from their digests to allow for
   * nice error messages. */
  plain_digest = htonl(entry->fnv1_checksum);
  expected = svn_checksum__from_digest_fnv1a_32x4(
                (const unsigned char *)&plain_digest, result_pool);
  plain_digest = htonl(digest);
  actual = svn_checksum__from_digest_fnv1a_32x4(
                (const unsigned char *)&plain_digest, result_pool);

  /* Construct the full error message with all the info we have. */
  return svn_checksum_mismatch_err(expected, actual, result_pool,
                 _("Low-level checksum mismatch while reading\n"
                   "%s bytes of meta data at offset %s "),
                 apr_off_t_toa(result_pool, entry->size),
                 apr_off_t_toa(result_pool, entry->offset));
}