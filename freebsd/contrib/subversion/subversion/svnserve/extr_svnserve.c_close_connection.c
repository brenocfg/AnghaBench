#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  ref_count; } ;
typedef  TYPE_1__ connection_t ;

/* Variables and functions */
 scalar_t__ svn_atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_connection(connection_t *connection)
{
  /* this will automatically close USOCK */
  if (svn_atomic_dec(&connection->ref_count) == 0)
    svn_pool_destroy(connection->pool);
}