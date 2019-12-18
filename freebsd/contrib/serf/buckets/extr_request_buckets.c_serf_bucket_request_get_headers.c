#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_6__ {TYPE_1__* headers; } ;
typedef  TYPE_2__ request_context_t ;

/* Variables and functions */

serf_bucket_t *serf_bucket_request_get_headers(
    serf_bucket_t *bucket)
{
    return ((request_context_t *)bucket->data)->headers;
}