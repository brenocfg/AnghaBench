#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int example_hashes; int keyspace; int left; int backend_info; int show; int usage; int version; unsigned int bitmap_min; unsigned int bitmap_max; } ;
typedef  TYPE_1__ user_options_t ;
typedef  unsigned int u32 ;
struct TYPE_8__ {unsigned int digests_cnt; scalar_t__ st_digests_buf; scalar_t__ digests_buf; } ;
typedef  TYPE_2__ hashes_t ;
struct TYPE_9__ {int /*<<< orphan*/  dgst_pos3; int /*<<< orphan*/  dgst_pos2; int /*<<< orphan*/  dgst_pos1; int /*<<< orphan*/  dgst_pos0; int /*<<< orphan*/ * st_hash; int /*<<< orphan*/  dgst_size; } ;
typedef  TYPE_3__ hashconfig_t ;
struct TYPE_10__ {TYPE_1__* user_options; TYPE_2__* hashes; TYPE_3__* hashconfig; TYPE_5__* bitmap_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_11__ {int enabled; unsigned int bitmap_bits; unsigned int bitmap_nums; unsigned int bitmap_size; unsigned int bitmap_mask; unsigned int bitmap_shift1; unsigned int bitmap_shift2; unsigned int* bitmap_s1_a; unsigned int* bitmap_s1_b; unsigned int* bitmap_s1_c; unsigned int* bitmap_s1_d; unsigned int* bitmap_s2_a; unsigned int* bitmap_s2_b; unsigned int* bitmap_s2_c; unsigned int* bitmap_s2_d; } ;
typedef  TYPE_5__ bitmap_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BITMAP_FINAL_OVERFLOW ; 
 int /*<<< orphan*/  EVENT_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int generate_bitmaps (unsigned int,int /*<<< orphan*/ ,unsigned int const,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int) ; 
 scalar_t__ hcmalloc (unsigned int) ; 
 int /*<<< orphan*/  selftest_to_bitmap (unsigned int const,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

int bitmap_ctx_init (hashcat_ctx_t *hashcat_ctx)
{
  bitmap_ctx_t   *bitmap_ctx   = hashcat_ctx->bitmap_ctx;
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  hashes_t       *hashes       = hashcat_ctx->hashes;
  user_options_t *user_options = hashcat_ctx->user_options;

  bitmap_ctx->enabled = false;

  if (user_options->example_hashes == true) return 0;
  if (user_options->keyspace       == true) return 0;
  if (user_options->left           == true) return 0;
  if (user_options->backend_info   == true) return 0;
  if (user_options->show           == true) return 0;
  if (user_options->usage          == true) return 0;
  if (user_options->version        == true) return 0;

  bitmap_ctx->enabled = true;

  /**
   * generate bitmap tables
   */

  const u32 bitmap_shift1 = 5;
  const u32 bitmap_shift2 = 13;

  const u32 bitmap_min = user_options->bitmap_min;
  const u32 bitmap_max = user_options->bitmap_max;

  u32 *bitmap_s1_a = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s1_b = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s1_c = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s1_d = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s2_a = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s2_b = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s2_c = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));
  u32 *bitmap_s2_d = (u32 *) hcmalloc ((1U << bitmap_max) * sizeof (u32));

  u32 bitmap_bits;
  u32 bitmap_nums;
  u32 bitmap_mask;
  u32 bitmap_size;

  for (bitmap_bits = bitmap_min; bitmap_bits < bitmap_max; bitmap_bits++)
  {
    bitmap_nums = 1U << bitmap_bits;

    bitmap_mask = bitmap_nums - 1;

    bitmap_size = bitmap_nums * sizeof (u32);

    if ((hashes->digests_cnt & bitmap_mask) == hashes->digests_cnt) break;

    if (generate_bitmaps (hashes->digests_cnt, hashconfig->dgst_size, bitmap_shift1, (char *) hashes->digests_buf, hashconfig->dgst_pos0, hashconfig->dgst_pos1, hashconfig->dgst_pos2, hashconfig->dgst_pos3, bitmap_mask, bitmap_size, bitmap_s1_a, bitmap_s1_b, bitmap_s1_c, bitmap_s1_d, hashes->digests_cnt / 2) == true) continue;
    if (generate_bitmaps (hashes->digests_cnt, hashconfig->dgst_size, bitmap_shift2, (char *) hashes->digests_buf, hashconfig->dgst_pos0, hashconfig->dgst_pos1, hashconfig->dgst_pos2, hashconfig->dgst_pos3, bitmap_mask, bitmap_size, bitmap_s1_a, bitmap_s1_b, bitmap_s1_c, bitmap_s1_d, hashes->digests_cnt / 2) == true) continue;

    break;
  }

  if (bitmap_bits == bitmap_max)
  {
    EVENT_DATA (EVENT_BITMAP_FINAL_OVERFLOW, NULL, 0);
  }

  bitmap_nums = 1U << bitmap_bits;

  bitmap_mask = bitmap_nums - 1;

  bitmap_size = bitmap_nums * sizeof (u32);

  generate_bitmaps (hashes->digests_cnt, hashconfig->dgst_size, bitmap_shift1, (char *) hashes->digests_buf, hashconfig->dgst_pos0, hashconfig->dgst_pos1, hashconfig->dgst_pos2, hashconfig->dgst_pos3, bitmap_mask, bitmap_size, bitmap_s1_a, bitmap_s1_b, bitmap_s1_c, bitmap_s1_d, -1);
  generate_bitmaps (hashes->digests_cnt, hashconfig->dgst_size, bitmap_shift2, (char *) hashes->digests_buf, hashconfig->dgst_pos0, hashconfig->dgst_pos1, hashconfig->dgst_pos2, hashconfig->dgst_pos3, bitmap_mask, bitmap_size, bitmap_s2_a, bitmap_s2_b, bitmap_s2_c, bitmap_s2_d, -1);

  if (hashconfig->st_hash != NULL)
  {
    selftest_to_bitmap (bitmap_shift1, (char *) hashes->st_digests_buf, hashconfig->dgst_pos0, hashconfig->dgst_pos1, hashconfig->dgst_pos2, hashconfig->dgst_pos3, bitmap_mask, bitmap_s1_a, bitmap_s1_b, bitmap_s1_c, bitmap_s1_d);
    selftest_to_bitmap (bitmap_shift2, (char *) hashes->st_digests_buf, hashconfig->dgst_pos0, hashconfig->dgst_pos1, hashconfig->dgst_pos2, hashconfig->dgst_pos3, bitmap_mask, bitmap_s2_a, bitmap_s2_b, bitmap_s2_c, bitmap_s2_d);
  }

  bitmap_ctx->bitmap_bits   = bitmap_bits;
  bitmap_ctx->bitmap_nums   = bitmap_nums;
  bitmap_ctx->bitmap_size   = bitmap_size;
  bitmap_ctx->bitmap_mask   = bitmap_mask;
  bitmap_ctx->bitmap_shift1 = bitmap_shift1;
  bitmap_ctx->bitmap_shift2 = bitmap_shift2;

  bitmap_ctx->bitmap_s1_a   = bitmap_s1_a;
  bitmap_ctx->bitmap_s1_b   = bitmap_s1_b;
  bitmap_ctx->bitmap_s1_c   = bitmap_s1_c;
  bitmap_ctx->bitmap_s1_d   = bitmap_s1_d;
  bitmap_ctx->bitmap_s2_a   = bitmap_s2_a;
  bitmap_ctx->bitmap_s2_b   = bitmap_s2_b;
  bitmap_ctx->bitmap_s2_c   = bitmap_s2_c;
  bitmap_ctx->bitmap_s2_d   = bitmap_s2_d;

  return 0;
}