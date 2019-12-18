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
struct TYPE_5__ {char* data; int /*<<< orphan*/  remaining; } ;
typedef  TYPE_2__ eagain_baton_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 

__attribute__((used)) static apr_status_t
eagain_bucket_peek(serf_bucket_t *bucket,
                   const char **data,
                   apr_size_t *len)
{
  const eagain_baton_t *eab = bucket->data;

  *data = eab->data ? eab->data : "";
  *len = eab->remaining;

  return APR_SUCCESS;
}