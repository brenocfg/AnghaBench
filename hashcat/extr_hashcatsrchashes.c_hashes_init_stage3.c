#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int digests_cnt; int digests_offset; scalar_t__ digests_done; } ;
typedef  TYPE_1__ salt_t ;
struct TYPE_8__ {int digests_done; int* digests_shown; int salts_cnt; int salts_done; int* salts_shown; TYPE_1__* salts_buf; TYPE_4__* hashes_buf; } ;
typedef  TYPE_2__ hashes_t ;
struct TYPE_9__ {TYPE_2__* hashes; } ;
typedef  TYPE_3__ hashcat_ctx_t ;
struct TYPE_10__ {int cracked; } ;
typedef  TYPE_4__ hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  mycracked (TYPE_3__*) ; 

int hashes_init_stage3 (hashcat_ctx_t *hashcat_ctx)
{
  hashes_t *hashes = hashcat_ctx->hashes;

  u32  digests_done  = hashes->digests_done;
  u32 *digests_shown = hashes->digests_shown;

  u32  salts_cnt     = hashes->salts_cnt;
  u32  salts_done    = hashes->salts_done;
  u32 *salts_shown   = hashes->salts_shown;

  hash_t *hashes_buf = hashes->hashes_buf;

  salt_t *salts_buf  = hashes->salts_buf;

  for (u32 salt_idx = 0; salt_idx < salts_cnt; salt_idx++)
  {
    salt_t *salt_buf = salts_buf + salt_idx;

    u32 digests_cnt = salt_buf->digests_cnt;

    for (u32 digest_idx = 0; digest_idx < digests_cnt; digest_idx++)
    {
      const u32 hashes_idx = salt_buf->digests_offset + digest_idx;

      if (hashes_buf[hashes_idx].cracked == 1)
      {
        digests_shown[hashes_idx] = 1;

        digests_done++;

        salt_buf->digests_done++;
      }
    }

    if (salt_buf->digests_done == salt_buf->digests_cnt)
    {
      salts_shown[salt_idx] = 1;

      salts_done++;
    }

    if (salts_done == salts_cnt) mycracked (hashcat_ctx);
  }

  hashes->digests_done = digests_done;

  hashes->salts_cnt   = salts_cnt;
  hashes->salts_done  = salts_done;

  return 0;
}