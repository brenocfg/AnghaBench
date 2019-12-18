#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int /*<<< orphan*/ * data; } ;
struct cache_local_copy {int /*<<< orphan*/  location; } ;
struct amortization_counter {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  record ;
struct TYPE_8__ {int cnt; int flags; size_t heap_acounter_off; int /*<<< orphan*/  disk_filter; TYPE_1__* heap; } ;
typedef  TYPE_2__ cache_top_access_result_t ;
struct TYPE_9__ {int pos; int size; int /*<<< orphan*/  buff; } ;
typedef  TYPE_3__ cache_buffer_t ;
struct TYPE_7__ {struct cache_uri** H; } ;

/* Variables and functions */
 int amortization_counter_types ; 
 int /*<<< orphan*/  assert (struct cache_local_copy*) ; 
 int /*<<< orphan*/  cache_bclear (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  cache_bprintf (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  cache_get_uri_name (struct cache_uri*) ; 
 int /*<<< orphan*/  cache_local_copy_get_yellow_light_time (struct cache_local_copy*,int*,int*) ; 
 scalar_t__ cache_uri_get_acounter_value (struct cache_uri*,int) ; 
 int /*<<< orphan*/  cache_uri_get_size (struct cache_uri*) ; 
 struct cache_local_copy* cache_uri_local_copy_find (struct cache_uri*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int serialize_top_result_as_text (cache_top_access_result_t *R, char *output, int olen) {
  int k, o = 0;
  for (k = 1; k <= R->cnt; k++) {
    char record[2048];
    cache_buffer_t b;
    struct cache_uri *U = R->heap->H[k];
    cache_bclear (&b, record, sizeof (record));
    struct cache_local_copy *L = NULL;
    if (R->flags & 0x80000000) {
      L = cache_uri_local_copy_find (U, R->disk_filter);
      assert (L);
      cache_bprintf (&b, "%s\t", L->location);
    }
    cache_bprintf (&b, "%s", cache_get_uri_name (U));
    if (R->flags & 4) {
      int j;
      for (j = 0; j < amortization_counter_types; j++) {
        cache_bprintf (&b, "\t%.7lg", (double) cache_uri_get_acounter_value (U, j));
      }
    } else if (R->flags & 1) {
      struct amortization_counter *C = ((struct amortization_counter *) &U->data[R->heap_acounter_off]);
      cache_bprintf (&b, "\t%.7lg", (double) C->value);
    }

    if (R->flags & 2) {
      cache_bprintf (&b, "\t%lld", cache_uri_get_size (U));
    }

    if (R->flags & (32+64)) {
      int remaining_time = -1, elapsed_time = -1;
      assert (L);
      cache_local_copy_get_yellow_light_time (L, &remaining_time, &elapsed_time);
      if (R->flags & 32) {
        cache_bprintf (&b, "\t%d", remaining_time);
      }
      if (R->flags & 64) {
        cache_bprintf (&b, "\t%d", elapsed_time);
      }
    }

    cache_bprintf (&b, "\n");
    if (b.pos >= b.size) {
      break;
    }
    if (o + b.pos > olen) {
      break;
    }
    memcpy (output + o, b.buff, b.pos);
    o += b.pos;
  }
  return o;
}