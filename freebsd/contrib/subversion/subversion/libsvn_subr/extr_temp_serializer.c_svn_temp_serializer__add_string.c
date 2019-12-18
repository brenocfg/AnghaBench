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
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ svn_temp_serializer__context_t ;

/* Variables and functions */
 int /*<<< orphan*/  store_current_end_pointer (TYPE_1__*,void const* const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

void
svn_temp_serializer__add_string(svn_temp_serializer__context_t *context,
                                const char * const * s)
{
  const char *string = *s;

  /* Store the offset at which the string data that will the appended.
   * Write 0 for NULL pointers. Strings don't need special alignment. */
  store_current_end_pointer(context, (const void *const *)s);

  /* append the string data */
  if (string)
    svn_stringbuf_appendbytes(context->buffer, string, strlen(string) + 1);
}