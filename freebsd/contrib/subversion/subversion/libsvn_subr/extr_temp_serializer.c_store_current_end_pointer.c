#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* source; TYPE_1__* buffer; } ;
typedef  TYPE_3__ svn_temp_serializer__context_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_6__ {scalar_t__ target_offset; scalar_t__ source_struct; } ;
struct TYPE_5__ {scalar_t__ len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
store_current_end_pointer(svn_temp_serializer__context_t *context,
                          const void * const * source_pointer)
{
  apr_size_t ptr_offset;
  apr_size_t *target_ptr;

  /* if *source_pointer is the root struct, there will be no parent structure
   * to relate it to */
  if (context->source == NULL)
    return;

  /* position of the serialized pointer relative to the begin of the buffer */
  ptr_offset = (const char *)source_pointer
             - (const char *)context->source->source_struct
             + context->source->target_offset;

  /* the offset must be within the serialized data. Otherwise, you forgot
   * to serialize the respective sub-struct. */
  assert(context->buffer->len > ptr_offset);

  /* use the serialized pointer as a storage for the offset */
  target_ptr = (apr_size_t*)(context->buffer->data + ptr_offset);

  /* store the current buffer length because that's where we will append
   * the serialized data of the sub-struct or string */
  *target_ptr = *source_pointer == NULL
              ? 0
              : context->buffer->len - context->source->target_offset;
}