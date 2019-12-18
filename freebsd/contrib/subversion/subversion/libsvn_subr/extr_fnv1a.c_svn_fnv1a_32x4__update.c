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
struct TYPE_3__ {scalar_t__ buffered; void const* buffer; int /*<<< orphan*/  hashes; } ;
typedef  TYPE_1__ svn_fnv1a_32x4__context_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ SCALING ; 
 scalar_t__ fnv1a_32x4 (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void const*,char const*,scalar_t__) ; 

void
svn_fnv1a_32x4__update(svn_fnv1a_32x4__context_t *context,
                       const void *data,
                       apr_size_t len)
{
  apr_size_t processed;

  if (context->buffered)
    {
      apr_size_t to_copy = SCALING - context->buffered;
      if (to_copy > len)
        {
          memcpy(context->buffer + context->buffered, data, len);
          context->buffered += len;
          return;
        }

      memcpy(context->buffer + context->buffered, data, to_copy);
      data = (const char *)data + to_copy;
      len -= to_copy;

      fnv1a_32x4(context->hashes, context->buffer, SCALING);
      context->buffered = 0;
    }

  processed = fnv1a_32x4(context->hashes, data, len);
  if (processed != len)
    {
      context->buffered = len - processed;
      memcpy(context->buffer,
             (const char*)data + processed,
             len - processed);
    }
}