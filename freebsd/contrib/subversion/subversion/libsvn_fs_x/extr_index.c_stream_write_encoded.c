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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int ENCODED_INT_LENGTH ; 
 int /*<<< orphan*/  encode_uint (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
stream_write_encoded(svn_stream_t *stream,
                     apr_uint64_t value)
{
  unsigned char encoded[ENCODED_INT_LENGTH];

  apr_size_t len = encode_uint(encoded, value);
  return svn_error_trace(svn_stream_write(stream, (char *)encoded, &len));
}