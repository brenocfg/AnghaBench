#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ user_len; scalar_t__ user_name; } ;
typedef  TYPE_3__ user_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_22__ {scalar_t__ digests_cnt; scalar_t__ digests_offset; } ;
typedef  TYPE_4__ salt_t ;
struct TYPE_23__ {scalar_t__* tmp_buf; scalar_t__* out_buf; } ;
typedef  TYPE_5__ potfile_ctx_t ;
struct TYPE_24__ {int (* module_hash_binary_save ) (TYPE_7__*,scalar_t__,scalar_t__,char**) ;} ;
typedef  TYPE_6__ module_ctx_t ;
struct TYPE_25__ {scalar_t__ salts_cnt; scalar_t__* digests_shown; TYPE_4__* salts_buf; TYPE_10__* hashes_buf; } ;
typedef  TYPE_7__ hashes_t ;
struct TYPE_26__ {int opts_type; } ;
typedef  TYPE_8__ hashconfig_t ;
struct TYPE_27__ {TYPE_6__* module_ctx; TYPE_7__* hashes; TYPE_8__* hashconfig; TYPE_5__* potfile_ctx; } ;
typedef  TYPE_9__ hashcat_ctx_t ;
struct TYPE_18__ {TYPE_2__* hash_info; } ;
typedef  TYPE_10__ hash_t ;
struct TYPE_20__ {TYPE_3__* user; TYPE_1__* split; } ;
struct TYPE_19__ {scalar_t__ split_origin; int split_neighbor; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DATA (int /*<<< orphan*/ ,scalar_t__*,int const) ; 
 int /*<<< orphan*/  EVENT_POTFILE_HASH_LEFT ; 
 scalar_t__ HCBUFSIZ_LARGE ; 
 int MODULE_DEFAULT (TYPE_7__*,scalar_t__,scalar_t__,char**) ; 
 int OPTS_TYPE_BINARY_HASHFILE ; 
 int OPTS_TYPE_HASH_SPLIT ; 
 scalar_t__ SPLIT_ORIGIN_LEFT ; 
 scalar_t__ SPLIT_ORIGIN_NONE ; 
 int hash_encode (TYPE_8__*,TYPE_7__*,TYPE_6__*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 int outfile_write (TYPE_9__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,scalar_t__,char*) ; 
 int stub1 (TYPE_7__*,scalar_t__,scalar_t__,char**) ; 

int potfile_handle_left (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t  *hashconfig  = hashcat_ctx->hashconfig;
  hashes_t      *hashes      = hashcat_ctx->hashes;
  module_ctx_t  *module_ctx  = hashcat_ctx->module_ctx;
  potfile_ctx_t *potfile_ctx = hashcat_ctx->potfile_ctx;

  hash_t *hashes_buf = hashes->hashes_buf;

  u32     salts_cnt = hashes->salts_cnt;
  salt_t *salts_buf = hashes->salts_buf;

  if (hashconfig->opts_type & OPTS_TYPE_HASH_SPLIT)
  {
    // this implementation will work for LM only
    // however, LM is the only hash support which splits the password into multiple hashes

    for (u32 salt_idx = 0; salt_idx < salts_cnt; salt_idx++)
    {
      salt_t *salt_buf = salts_buf + salt_idx;

      u32 digests_cnt = salt_buf->digests_cnt;

      for (u32 digest_idx = 0; digest_idx < digests_cnt; digest_idx++)
      {
        const u32 hashes_idx = salt_buf->digests_offset + digest_idx;

        u32 *digests_shown = hashes->digests_shown;

        hash_t *hash1 = &hashes_buf[hashes_idx];
        hash_t *hash2 = NULL;

        int split_neighbor = -1;

        // find out if at least one of the parts has been cracked

        if (hash1->hash_info->split->split_origin == SPLIT_ORIGIN_LEFT)
        {
          split_neighbor = hash1->hash_info->split->split_neighbor;

          hash2 = &hashes_buf[split_neighbor];

          if ((digests_shown[hashes_idx] == 1) && (digests_shown[split_neighbor] == 1)) continue;
        }
        else if (hash1->hash_info->split->split_origin == SPLIT_ORIGIN_NONE)
        {
          if (digests_shown[hashes_idx] == 1) continue;
        }
        else
        {
          // SPLIT_ORIGIN_RIGHT are not handled this way

          continue;
        }

        u8 *out_buf = potfile_ctx->out_buf;

        int out_len = hash_encode (hashcat_ctx->hashconfig, hashcat_ctx->hashes, hashcat_ctx->module_ctx, (char *) out_buf + 0, HCBUFSIZ_LARGE - 0, salt_idx, digest_idx);

        if (hash2)
        {
          out_len += hash_encode (hashcat_ctx->hashconfig, hashcat_ctx->hashes, hashcat_ctx->module_ctx, (char *) out_buf + 16, HCBUFSIZ_LARGE - 16, salt_idx, split_neighbor);
        }

        out_buf[out_len] = 0;

        // user
        unsigned char *username = NULL;

        u32 user_len = 0;

        user_t *user = hash1->hash_info->user;

        if (user)
        {
          username = (unsigned char *) (user->user_name);

          user_len = user->user_len;

          username[user_len] = 0;
        }

        u8 *tmp_buf = potfile_ctx->tmp_buf;

        tmp_buf[0] = 0;

        const int tmp_len = outfile_write (hashcat_ctx, (char *) out_buf, out_len, NULL, 0, 0, username, user_len, (char *) tmp_buf);

        EVENT_DATA (EVENT_POTFILE_HASH_LEFT, tmp_buf, tmp_len);
      }
    }
  }
  else
  {
    for (u32 salt_idx = 0; salt_idx < salts_cnt; salt_idx++)
    {
      salt_t *salt_buf = salts_buf + salt_idx;

      u32 digests_cnt = salt_buf->digests_cnt;

      for (u32 digest_idx = 0; digest_idx < digests_cnt; digest_idx++)
      {
        const u32 hashes_idx = salt_buf->digests_offset + digest_idx;

        u32 *digests_shown = hashes->digests_shown;

        if (digests_shown[hashes_idx] == 1) continue;

        u8 *out_buf = potfile_ctx->out_buf;

        int out_len;

        if (module_ctx->module_hash_binary_save != MODULE_DEFAULT)
        {
          char *binary_buf = NULL;

          int binary_len = module_ctx->module_hash_binary_save (hashes, salt_idx, digest_idx, &binary_buf);

          if ((hashconfig->opts_type & OPTS_TYPE_BINARY_HASHFILE) == 0)
          {
            binary_len--; // no need for the newline
          }

          memcpy (out_buf, binary_buf, binary_len);

          out_len = binary_len;

          hcfree (binary_buf);
        }
        else
        {
          out_len = hash_encode (hashcat_ctx->hashconfig, hashcat_ctx->hashes, hashcat_ctx->module_ctx, (char *) out_buf, HCBUFSIZ_LARGE, salt_idx, digest_idx);
        }

        out_buf[out_len] = 0;

        hash_t *hash = &hashes_buf[hashes_idx];

        // user
        unsigned char *username = NULL;

        u32 user_len = 0;

        if (hash->hash_info != NULL)
        {
          user_t *user = hash->hash_info->user;

          if (user)
          {
            username = (unsigned char *) (user->user_name);

            user_len = user->user_len;

            username[user_len] = 0;
          }
        }

        u8 *tmp_buf = potfile_ctx->tmp_buf;

        tmp_buf[0] = 0;

        const int tmp_len = outfile_write (hashcat_ctx, (char *) out_buf, out_len, NULL, 0, 0, username, user_len, (char *) tmp_buf);

        EVENT_DATA (EVENT_POTFILE_HASH_LEFT, tmp_buf, tmp_len);
      }
    }
  }

  return 0;
}