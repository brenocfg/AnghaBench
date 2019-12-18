#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hit_eof; } ;
typedef  TYPE_1__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EAGAIN ; 

__attribute__((used)) static apr_status_t detect_eof(void *baton, serf_bucket_t *aggregate_bucket)
{
    serf_connection_t *conn = baton;
    conn->hit_eof = 1;
    return APR_EAGAIN;
}