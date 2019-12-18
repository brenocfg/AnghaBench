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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; void* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ window; } ;
typedef  TYPE_3__ svn_fs_fs__raw_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_temp_serializer__add_leaf (int /*<<< orphan*/ *,void const* const*,scalar_t__) ; 
 TYPE_2__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__serialize_raw_window(void **buffer,
                                apr_size_t *buffer_size,
                                void *item,
                                apr_pool_t *pool)
{
  svn_fs_fs__raw_cached_window_t *window = item;
  svn_stringbuf_t *serialized;

  /* initialize the serialization process and allocate a buffer large
   * enough to do prevent re-allocations. */
  svn_temp_serializer__context_t *context =
      svn_temp_serializer__init(window,
                                sizeof(*window),
                                sizeof(*window) + window->window.len + 16,
                                pool);

  /* serialize the sub-structure(s) */
  svn_temp_serializer__add_leaf(context,
                                (const void * const *)&window->window.data,
                                window->window.len + 1);

  /* return the serialized result */
  serialized = svn_temp_serializer__get(context);

  *buffer = serialized->data;
  *buffer_size = serialized->len;

  return SVN_NO_ERROR;
}