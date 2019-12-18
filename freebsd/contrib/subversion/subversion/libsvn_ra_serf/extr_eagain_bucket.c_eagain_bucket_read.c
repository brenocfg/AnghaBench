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
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_5__ {scalar_t__ remaining; char* data; } ;
typedef  TYPE_2__ eagain_baton_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EAGAIN ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ SERF_READ_ALL_AVAIL ; 

__attribute__((used)) static apr_status_t
eagain_bucket_read(serf_bucket_t *bucket,
                   apr_size_t requested,
                   const char **data,
                   apr_size_t *len)
{
  eagain_baton_t *eab = bucket->data;

  if (eab->remaining > 0)
    {
      *data = eab->data;
      if (requested > eab->remaining || requested == SERF_READ_ALL_AVAIL)
        {
          *len = eab->remaining;
          eab->data = NULL;
          eab->remaining = 0;
        }
      else
        {
          *len = requested;
          eab->data += requested;
          eab->remaining -= requested;
        }

      if (eab->remaining)
        return APR_SUCCESS;
    }

  return APR_EAGAIN;
}