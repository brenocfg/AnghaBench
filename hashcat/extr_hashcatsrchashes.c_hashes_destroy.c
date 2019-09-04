#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int username; } ;
typedef  TYPE_1__ user_options_t ;
typedef  size_t u32 ;
struct TYPE_9__ {size_t hashes_cnt; TYPE_6__** st_hook_salts_buf; TYPE_6__** st_esalts_buf; TYPE_6__** st_salts_buf; TYPE_6__** st_digests_buf; TYPE_6__** tmp_buf; TYPE_6__** out_buf; TYPE_6__** hook_salts_buf; TYPE_6__** esalts_buf; TYPE_6__** hash_info; TYPE_6__** salts_shown; TYPE_6__** salts_buf; TYPE_6__** digests_shown_tmp; TYPE_6__** digests_shown; TYPE_6__** digests_buf; } ;
typedef  TYPE_2__ hashes_t ;
struct TYPE_10__ {int opts_type; } ;
typedef  TYPE_3__ hashconfig_t ;
struct TYPE_11__ {TYPE_1__* user_options; TYPE_2__* hashes; TYPE_3__* hashconfig; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_12__ {struct TYPE_12__** split; struct TYPE_12__** orighash; struct TYPE_12__** user; } ;

/* Variables and functions */
 int OPTS_TYPE_HASH_COPY ; 
 int OPTS_TYPE_HASH_SPLIT ; 
 int /*<<< orphan*/  hcfree (TYPE_6__**) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void hashes_destroy (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  hashes_t       *hashes       = hashcat_ctx->hashes;
  user_options_t *user_options = hashcat_ctx->user_options;

  hcfree (hashes->digests_buf);
  hcfree (hashes->digests_shown);
  hcfree (hashes->digests_shown_tmp);

  hcfree (hashes->salts_buf);
  hcfree (hashes->salts_shown);

  if ((user_options->username == true) || (hashconfig->opts_type & OPTS_TYPE_HASH_COPY))
  {
    for (u32 hash_pos = 0; hash_pos < hashes->hashes_cnt; hash_pos++)
    {
      if (user_options->username == true)
      {
        hcfree (hashes->hash_info[hash_pos]->user);
      }

      if (hashconfig->opts_type & OPTS_TYPE_HASH_COPY)
      {
        hcfree (hashes->hash_info[hash_pos]->orighash);
      }

      if (hashconfig->opts_type & OPTS_TYPE_HASH_SPLIT)
      {
        hcfree (hashes->hash_info[hash_pos]->split);
      }
    }
  }

  hcfree (hashes->hash_info);

  hcfree (hashes->esalts_buf);
  hcfree (hashes->hook_salts_buf);

  hcfree (hashes->out_buf);
  hcfree (hashes->tmp_buf);

  hcfree (hashes->st_digests_buf);
  hcfree (hashes->st_salts_buf);
  hcfree (hashes->st_esalts_buf);
  hcfree (hashes->st_hook_salts_buf);

  memset (hashes, 0, sizeof (hashes_t));
}