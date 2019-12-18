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
struct TYPE_4__ {void* by_path; void* by_repository; } ;
typedef  TYPE_1__ svn_client__committables_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
create_committables(svn_client__committables_t **committables,
                    apr_pool_t *pool)
{
  *committables = apr_palloc(pool, sizeof(**committables));

  (*committables)->by_repository = apr_hash_make(pool);
  (*committables)->by_path = apr_hash_make(pool);
}