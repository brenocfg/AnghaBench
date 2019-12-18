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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
typedef  int apr_size_t ;
struct TYPE_3__ {int elt_size; scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_temp_serializer__add_leaf (int /*<<< orphan*/ *,void const* const*,int) ; 
 int /*<<< orphan*/  svn_temp_serializer__pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__push (int /*<<< orphan*/ *,void const* const*,int) ; 

void
svn_fs_x__serialize_apr_array(svn_temp_serializer__context_t *context,
                              apr_array_header_t **a)
{
  const apr_array_header_t *array = *a;

  /* Nothing to do for NULL string references. */
  if (array == NULL)
    return;

  /* array header struct */
  svn_temp_serializer__push(context,
                            (const void * const *)a,
                            sizeof(*array));

  /* contents */
  svn_temp_serializer__add_leaf(context,
                                (const void * const *)&array->elts,
                                (apr_size_t)array->nelts * array->elt_size);

  /* back to the caller's nesting level */
  svn_temp_serializer__pop(context);
}