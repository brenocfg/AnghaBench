#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* source; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * recycler; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ svn_temp_serializer__context_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * upper; scalar_t__ target_offset; void const* source_struct; } ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_create_ensure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_temp_serializer__context_t *
svn_temp_serializer__init(const void *source_struct,
                          apr_size_t struct_size,
                          apr_size_t suggested_buffer_size,
                          apr_pool_t *pool)
{
  /* select a meaningful initial memory buffer capacity */
  apr_size_t init_size = suggested_buffer_size < struct_size
                       ? struct_size
                       : suggested_buffer_size;

  /* create the serialization context and initialize it */
  svn_temp_serializer__context_t *context = apr_palloc(pool, sizeof(*context));
  context->pool = pool;
  context->buffer = svn_stringbuf_create_ensure(init_size, pool);
  context->recycler = NULL;

  /* If a source struct has been given, make it the root struct. */
  if (source_struct)
    {
      context->source = apr_palloc(pool, sizeof(*context->source));
      context->source->source_struct = source_struct;
      context->source->target_offset = 0;
      context->source->upper = NULL;

      /* serialize, i.e. append, the content of the first structure */
      svn_stringbuf_appendbytes(context->buffer, source_struct, struct_size);
    }
    else
    {
      /* The root struct will be set with the first push() op, or not at all
       * (in case of a plain string). */
      context->source = NULL;
    }

  /* done */
  return context;
}