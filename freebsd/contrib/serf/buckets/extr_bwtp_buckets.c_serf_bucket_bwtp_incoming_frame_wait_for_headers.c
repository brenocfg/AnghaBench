#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ serf_bucket_t ;
typedef  int /*<<< orphan*/  incoming_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  wait_for_body (TYPE_1__*,int /*<<< orphan*/ *) ; 

apr_status_t serf_bucket_bwtp_incoming_frame_wait_for_headers(
    serf_bucket_t *bucket)
{
    incoming_context_t *ctx = bucket->data;

    return wait_for_body(bucket, ctx);
}