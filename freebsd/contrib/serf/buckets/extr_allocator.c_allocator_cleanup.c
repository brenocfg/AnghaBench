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
struct TYPE_2__ {int /*<<< orphan*/  allocator; scalar_t__ own_allocator; scalar_t__ blocks; } ;
typedef  TYPE_1__ serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_allocator_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_allocator_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static apr_status_t allocator_cleanup(void *data)
{
    serf_bucket_alloc_t *allocator = data;

    /* If we allocated anything, give it back. */
    if (allocator->blocks) {
        apr_allocator_free(allocator->allocator, allocator->blocks);
    }

    /* If we allocated our own allocator (?!), destroy it here. */
    if (allocator->own_allocator) {
        apr_allocator_destroy(allocator->allocator);
    }

    return APR_SUCCESS;
}