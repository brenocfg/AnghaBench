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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int apr_uint64_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int apr_byte_t ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_read_full2 (int /*<<< orphan*/ *,int*,int,int*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_uint64_from_proto_index(apr_file_t *proto_index,
                             apr_uint64_t *value_p,
                             svn_boolean_t *eof,
                             apr_pool_t *scratch_pool)
{
  apr_byte_t buffer[sizeof(*value_p)];
  apr_size_t bytes_read;

  /* Read the full 8 bytes or our 64 bit value, unless we hit EOF.
   * Assert that we never read partial values. */
  SVN_ERR(svn_io_file_read_full2(proto_index, buffer, sizeof(buffer),
                                 &bytes_read, eof, scratch_pool));
  SVN_ERR_ASSERT((eof && *eof) || bytes_read == sizeof(buffer));

  /* If we did not hit EOF, reconstruct the uint64 value and return it. */
  if (!eof || !*eof)
    {
      int i;
      apr_uint64_t value;

      /* This could only overflow if CHAR_BIT had a value that is not
       * a divisor of 64. */
      value = 0;
      for (i = sizeof(buffer) - 1; i >= 0; --i)
        value = (value << CHAR_BIT) + buffer[i];

      *value_p = value;
    }

  return SVN_NO_ERROR;
}