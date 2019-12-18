#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct rar_br {int cache_avail; int avail_in; int cache_buffer; int /*<<< orphan*/ * next_in; } ;
struct rar {scalar_t__ bytes_unconsumed; scalar_t__ bytes_remaining; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int CACHE_BITS ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int /*<<< orphan*/ * rar_read_ahead (struct archive_read*,int,scalar_t__*) ; 

__attribute__((used)) static int
rar_br_fillup(struct archive_read *a, struct rar_br *br)
{
  struct rar *rar = (struct rar *)(a->format->data);
  int n = CACHE_BITS - br->cache_avail;

  for (;;) {
    switch (n >> 3) {
    case 8:
      if (br->avail_in >= 8) {
        br->cache_buffer =
            ((uint64_t)br->next_in[0]) << 56 |
            ((uint64_t)br->next_in[1]) << 48 |
            ((uint64_t)br->next_in[2]) << 40 |
            ((uint64_t)br->next_in[3]) << 32 |
            ((uint32_t)br->next_in[4]) << 24 |
            ((uint32_t)br->next_in[5]) << 16 |
            ((uint32_t)br->next_in[6]) << 8 |
             (uint32_t)br->next_in[7];
        br->next_in += 8;
        br->avail_in -= 8;
        br->cache_avail += 8 * 8;
        rar->bytes_unconsumed += 8;
        rar->bytes_remaining -= 8;
        return (1);
      }
      break;
    case 7:
      if (br->avail_in >= 7) {
        br->cache_buffer =
           (br->cache_buffer << 56) |
            ((uint64_t)br->next_in[0]) << 48 |
            ((uint64_t)br->next_in[1]) << 40 |
            ((uint64_t)br->next_in[2]) << 32 |
            ((uint32_t)br->next_in[3]) << 24 |
            ((uint32_t)br->next_in[4]) << 16 |
            ((uint32_t)br->next_in[5]) << 8 |
             (uint32_t)br->next_in[6];
        br->next_in += 7;
        br->avail_in -= 7;
        br->cache_avail += 7 * 8;
        rar->bytes_unconsumed += 7;
        rar->bytes_remaining -= 7;
        return (1);
      }
      break;
    case 6:
      if (br->avail_in >= 6) {
        br->cache_buffer =
           (br->cache_buffer << 48) |
            ((uint64_t)br->next_in[0]) << 40 |
            ((uint64_t)br->next_in[1]) << 32 |
            ((uint32_t)br->next_in[2]) << 24 |
            ((uint32_t)br->next_in[3]) << 16 |
            ((uint32_t)br->next_in[4]) << 8 |
             (uint32_t)br->next_in[5];
        br->next_in += 6;
        br->avail_in -= 6;
        br->cache_avail += 6 * 8;
        rar->bytes_unconsumed += 6;
        rar->bytes_remaining -= 6;
        return (1);
      }
      break;
    case 0:
      /* We have enough compressed data in
       * the cache buffer.*/
      return (1);
    default:
      break;
    }
    if (br->avail_in <= 0) {

      if (rar->bytes_unconsumed > 0) {
        /* Consume as much as the decompressor
         * actually used. */
        __archive_read_consume(a, rar->bytes_unconsumed);
        rar->bytes_unconsumed = 0;
      }
      br->next_in = rar_read_ahead(a, 1, &(br->avail_in));
      if (br->next_in == NULL)
        return (0);
      if (br->avail_in == 0)
        return (0);
    }
    br->cache_buffer =
       (br->cache_buffer << 8) | *br->next_in++;
    br->avail_in--;
    br->cache_avail += 8;
    n -= 8;
    rar->bytes_unconsumed++;
    rar->bytes_remaining--;
  }
}