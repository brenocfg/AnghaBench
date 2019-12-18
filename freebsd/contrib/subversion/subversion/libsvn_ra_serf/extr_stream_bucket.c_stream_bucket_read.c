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
struct TYPE_4__ {int /*<<< orphan*/  databuf; } ;
typedef  TYPE_1__ stream_bucket_ctx_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_databuf_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
stream_bucket_read(serf_bucket_t *bucket, apr_size_t requested,
                   const char **data, apr_size_t *len)
{
  stream_bucket_ctx_t *ctx = bucket->data;

  return serf_databuf_read(&ctx->databuf, requested, data, len);
}