#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_4__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_5__ {TYPE_1__ id; int /*<<< orphan*/  kind; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ svn_fs_x__dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_byte_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__MAX_ENCODED_UINT_LEN ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn__encode_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn__encode_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char const*,int*) ; 

__attribute__((used)) static svn_error_t *
unparse_dir_entry(svn_fs_x__dirent_t *dirent,
                  svn_stream_t *stream,
                  apr_pool_t *scratch_pool)
{
  apr_size_t to_write;
  apr_size_t name_len = strlen(dirent->name);

  /* A buffer with sufficient space for 
   * - entry name + 1 terminating NUL
   * - 1 byte for the node kind
   * - 2 numbers in 7b/8b encoding for the noderev-id
   */
  apr_byte_t *buffer = apr_palloc(scratch_pool,
                                  name_len + 2 + 2 * SVN__MAX_ENCODED_UINT_LEN);

  /* Now construct the value. */
  apr_byte_t *p = buffer;

  /* The entry name, terminated by NUL. */
  memcpy(p, dirent->name, name_len + 1);
  p += name_len + 1;

  /* The entry type. */
  p = svn__encode_uint(p, dirent->kind);

  /* The ID. */
  p = svn__encode_int(p, dirent->id.change_set);
  p = svn__encode_uint(p, dirent->id.number);

  /* Add the entry to the output stream. */
  to_write = p - buffer;
  SVN_ERR(svn_stream_write(stream, (const char *)buffer, &to_write));

  return SVN_NO_ERROR;
}