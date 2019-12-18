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
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  allocator; } ;
typedef  TYPE_1__ serf_bucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_default_destroy (TYPE_1__*) ; 

void serf_default_destroy_and_data(serf_bucket_t *bucket)
{
    serf_bucket_mem_free(bucket->allocator, bucket->data);
    serf_default_destroy(bucket);
}