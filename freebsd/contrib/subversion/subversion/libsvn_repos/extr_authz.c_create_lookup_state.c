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
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_4__ {void* parent_path; void* scratch_pad; void* current; void* next; } ;
typedef  TYPE_1__ lookup_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lookup_state_t *
create_lookup_state(apr_pool_t *result_pool)
{
  lookup_state_t *state = apr_pcalloc(result_pool, sizeof(*state));
 
  state->next = apr_array_make(result_pool, 4, sizeof(node_t *));
  state->current = apr_array_make(result_pool, 4, sizeof(node_t *));

  /* Virtually all path segments should fit into this buffer.  If they
   * don't, the buffer gets automatically reallocated.
   *
   * Using a smaller initial size would be fine as well but does not
   * buy us much for the increased risk of being expanded anyway - at
   * some extra cost. */
  state->scratch_pad = svn_stringbuf_create_ensure(200, result_pool);

  /* Most paths should fit into this buffer.  The same rationale as
   * above applies. */
  state->parent_path = svn_stringbuf_create_ensure(200, result_pool);

  return state;
}