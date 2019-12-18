#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void
svn_temp_deserializer__resolve(const void *buffer, void **ptr)
{
  /* All pointers are stored as offsets to the buffer start
   * (of the respective serialized sub-struct). */
  apr_size_t ptr_offset = *(apr_size_t *)ptr;
  if (ptr_offset)
    {
      /* Reconstruct the original pointer value */
      const char *target = (const char *)buffer + ptr_offset;

      /* All sub-structs are written _after_ their respective parent.
       * Thus, all offsets are > 0. If the following assertion is not met,
       * the data is either corrupt or you tried to resolve the pointer
       * more than once. */
      assert(target > (const char *)buffer);

      /* replace the PTR_OFFSET in *ptr with the pointer to TARGET */
      (*(const char **)ptr) = target;
    }
  else
    {
      /* NULL pointers are stored as 0 which might have a different
       * binary representation. */
      *ptr = NULL;
    }
}