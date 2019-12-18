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
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SERF_READ_ALL_AVAIL ; 
 scalar_t__ serf_bucket_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
drain_bucket(serf_bucket_t *bucket)
{
  /* Read whatever is in the bucket, and just drop it.  */
  while (1)
    {
      apr_status_t status;
      const char *data;
      apr_size_t len;

      status = serf_bucket_read(bucket, SERF_READ_ALL_AVAIL, &data, &len);
      if (status)
        return status;
    }
}