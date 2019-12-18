#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_8__ {scalar_t__ len; void* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
struct TYPE_9__ {TYPE_6__* window; } ;
typedef  TYPE_3__ svn_fs_x__txdelta_cached_window_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {TYPE_1__* new_data; } ;
struct TYPE_7__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  serialize_txdeltawindow (int /*<<< orphan*/ *,TYPE_6__**) ; 
 TYPE_2__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__serialize_txdelta_window(void **buffer,
                                   apr_size_t *buffer_size,
                                   void *item,
                                   apr_pool_t *pool)
{
  svn_fs_x__txdelta_cached_window_t *window_info = item;
  svn_stringbuf_t *serialized;

  /* initialize the serialization process and allocate a buffer large
   * enough to do without the need of re-allocations in most cases. */
  apr_size_t text_len = window_info->window->new_data
                      ? window_info->window->new_data->len
                      : 0;
  svn_temp_serializer__context_t *context =
      svn_temp_serializer__init(window_info,
                                sizeof(*window_info),
                                500 + text_len,
                                pool);

  /* serialize the sub-structure(s) */
  serialize_txdeltawindow(context, &window_info->window);

  /* return the serialized result */
  serialized = svn_temp_serializer__get(context);

  *buffer = serialized->data;
  *buffer_size = serialized->len;

  return SVN_NO_ERROR;
}