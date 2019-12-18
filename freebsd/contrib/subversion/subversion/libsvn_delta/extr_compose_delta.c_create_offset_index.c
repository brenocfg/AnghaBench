#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_ops; TYPE_1__* ops; } ;
typedef  TYPE_2__ svn_txdelta_window_t ;
struct TYPE_8__ {int length; void** offs; } ;
typedef  TYPE_3__ offset_index_t ;
typedef  void* apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {scalar_t__ length; } ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static offset_index_t *
create_offset_index(const svn_txdelta_window_t *window, apr_pool_t *pool)
{
  offset_index_t *ndx = apr_palloc(pool, sizeof(*ndx));
  apr_size_t offset = 0;
  int i;

  ndx->length = window->num_ops;
  ndx->offs = apr_palloc(pool, (ndx->length + 1) * sizeof(*ndx->offs));

  for (i = 0; i < ndx->length; ++i)
    {
      ndx->offs[i] = offset;
      offset += window->ops[i].length;
    }
  ndx->offs[ndx->length] = offset;

  return ndx;
}