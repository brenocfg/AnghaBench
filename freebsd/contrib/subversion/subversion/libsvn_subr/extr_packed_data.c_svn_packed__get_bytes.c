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
struct TYPE_5__ {TYPE_1__* packed; int /*<<< orphan*/  lengths_stream; } ;
typedef  TYPE_2__ svn_packed__byte_stream_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_4__ {char* data; scalar_t__ len; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  svn_packed__get_uint (int /*<<< orphan*/ ) ; 

const char *
svn_packed__get_bytes(svn_packed__byte_stream_t *stream,
                      apr_size_t *len)
{
  const char *result = stream->packed->data;
  apr_size_t count = (apr_size_t)svn_packed__get_uint(stream->lengths_stream);

  if (count > stream->packed->len)
    count = stream->packed->len;

  /* advance packed buffer */
  stream->packed->data += count;
  stream->packed->len -= count;
  stream->packed->blocksize -= count;

  *len = count;
  return result;
}