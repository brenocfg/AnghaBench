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
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_6__ {scalar_t__ body; scalar_t__ headers; } ;
typedef  TYPE_2__ request_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_destroy (scalar_t__) ; 
 int /*<<< orphan*/  serf_default_destroy_and_data (TYPE_1__*) ; 

__attribute__((used)) static void serf_request_destroy(serf_bucket_t *bucket)
{
  request_context_t *ctx = bucket->data;

  serf_bucket_destroy(ctx->headers);

  if (ctx->body)
    serf_bucket_destroy(ctx->body);

  serf_default_destroy_and_data(bucket);
}