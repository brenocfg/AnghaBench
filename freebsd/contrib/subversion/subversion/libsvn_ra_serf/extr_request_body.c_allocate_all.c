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
struct TYPE_3__ {int /*<<< orphan*/ * collect_bucket; scalar_t__ total_bytes; } ;
typedef  TYPE_1__ svn_ra_serf__request_body_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_EOF ; 
 int /*<<< orphan*/  SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 char* apr_pcalloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ serf_bucket_read (int /*<<< orphan*/ *,scalar_t__,char const**,scalar_t__*) ; 

__attribute__((used)) static const char *
allocate_all(svn_ra_serf__request_body_t *body,
             apr_pool_t *result_pool)
{
  char *buffer = apr_pcalloc(result_pool, body->total_bytes);
  const char *data;
  apr_size_t sz;
  apr_status_t s;
  apr_size_t remaining = body->total_bytes;
  char *next = buffer;

  while (!(s = serf_bucket_read(body->collect_bucket, remaining, &data, &sz)))
    {
      memcpy(next, data, sz);
      remaining -= sz;
      next += sz;

      if (! remaining)
        break;
    }

  if (!SERF_BUCKET_READ_ERROR(s))
    {
      memcpy(next, data, sz);
    }

  serf_bucket_destroy(body->collect_bucket);
  body->collect_bucket = NULL;

  return (s != APR_EOF) ? NULL : buffer;
}