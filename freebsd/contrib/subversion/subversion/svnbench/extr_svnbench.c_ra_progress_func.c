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
struct TYPE_2__ {int /*<<< orphan*/  bytes_transferred; } ;
typedef  TYPE_1__ ra_progress_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */

__attribute__((used)) static void
ra_progress_func(apr_off_t progress,
                 apr_off_t total,
                 void *baton,
                 apr_pool_t *pool)
{
  ra_progress_baton_t *b = baton;
  b->bytes_transferred = progress;
}