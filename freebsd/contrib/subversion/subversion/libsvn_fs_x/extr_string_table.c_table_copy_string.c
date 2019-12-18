#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; TYPE_2__* short_strings; } ;
typedef  TYPE_1__ string_sub_table_t ;
struct TYPE_6__ {size_t head_length; int tail_start; size_t head_string; } ;
typedef  TYPE_2__ string_header_t ;
typedef  int const apr_uint64_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* copy_masks ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
table_copy_string(char *buffer,
                  apr_size_t len,
                  const string_sub_table_t *table,
                  string_header_t *header)
{
  buffer[len] = '\0';
  do
    {
      assert(header->head_length <= len);
        {
#if SVN_UNALIGNED_ACCESS_IS_OK
          /* the sections that we copy tend to be short but we can copy
             *all* of it chunky because we made sure that source and target
             buffer have some extra padding to prevent segfaults. */
          apr_uint64_t mask;
          apr_size_t to_copy = len - header->head_length;
          apr_size_t copied = 0;

          const char *source = table->data + header->tail_start;
          char *target = buffer + header->head_length;
          len = header->head_length;

          /* copy whole chunks */
          while (to_copy >= copied + sizeof(apr_uint64_t))
            {
              *(apr_uint64_t *)(target + copied)
                = *(const apr_uint64_t *)(source + copied);
              copied += sizeof(apr_uint64_t);
            }

          /* copy the remainder assuming that we have up to 8 extra bytes
             of addressable buffer on the source and target sides.
             Now, we simply copy 8 bytes and use a mask to filter & merge
             old with new data. */
          mask = *(const apr_uint64_t *)copy_masks[to_copy - copied];
          *(apr_uint64_t *)(target + copied)
            = (*(apr_uint64_t *)(target + copied) & mask)
            | (*(const apr_uint64_t *)(source + copied) & ~mask);
#else
          memcpy(buffer + header->head_length,
                 table->data + header->tail_start,
                 len - header->head_length);
          len = header->head_length;
#endif
        }

      header = &table->short_strings[header->head_string];
    }
  while (len);
}