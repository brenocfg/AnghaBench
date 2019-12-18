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
struct TYPE_5__ {int /*<<< orphan*/ * our_stream; } ;
typedef  TYPE_1__ ssl_context_t ;
struct TYPE_6__ {TYPE_1__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_ssl_destroy_and_data (TYPE_2__*) ; 

__attribute__((used)) static void serf_ssl_decrypt_destroy_and_data(serf_bucket_t *bucket)
{
    ssl_context_t *ctx = bucket->data;

    serf_bucket_destroy(*ctx->our_stream);

    serf_ssl_destroy_and_data(bucket);
}