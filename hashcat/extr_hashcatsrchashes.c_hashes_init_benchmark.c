#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int benchmark; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int /*<<< orphan*/  user_options_extra_t ;
typedef  void salt_t ;
struct TYPE_16__ {void* (* module_benchmark_hook_salt ) (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ;void* (* module_benchmark_esalt ) (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ;void* (* module_benchmark_salt ) (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_2__ module_ctx_t ;
struct TYPE_17__ {void* st_salts_buf; void* st_esalts_buf; void* st_hook_salts_buf; int /*<<< orphan*/  hook_salts_buf; int /*<<< orphan*/  esalts_buf; int /*<<< orphan*/  salts_buf; } ;
typedef  TYPE_3__ hashes_t ;
struct TYPE_18__ {int is_salted; int esalt_size; int hook_salt_size; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_19__ {int /*<<< orphan*/ * user_options_extra; TYPE_1__* user_options; TYPE_2__* module_ctx; TYPE_3__* hashes; TYPE_4__* hashconfig; } ;
typedef  TYPE_5__ hashcat_ctx_t ;

/* Variables and functions */
 void* MODULE_DEFAULT (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hcfree (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 void* stub1 (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 void* stub2 (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 void* stub3 (TYPE_4__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 

int hashes_init_benchmark (hashcat_ctx_t *hashcat_ctx)
{
  const hashconfig_t          *hashconfig         = hashcat_ctx->hashconfig;
        hashes_t              *hashes             = hashcat_ctx->hashes;
  const module_ctx_t          *module_ctx         = hashcat_ctx->module_ctx;
  const user_options_t        *user_options       = hashcat_ctx->user_options;
  const user_options_extra_t  *user_options_extra = hashcat_ctx->user_options_extra;

  if (user_options->benchmark == false) return 0;

  if (hashconfig->is_salted == false) return 0;

  if (module_ctx->module_benchmark_salt != MODULE_DEFAULT)
  {
    salt_t *ptr = module_ctx->module_benchmark_salt (hashconfig, user_options, user_options_extra);

    memcpy (hashes->salts_buf, ptr, sizeof (salt_t));

    hcfree (ptr);
  }
  else
  {
    memcpy (hashes->salts_buf, hashes->st_salts_buf, sizeof (salt_t));
  }

  if (hashconfig->esalt_size > 0)
  {
    if (module_ctx->module_benchmark_esalt != MODULE_DEFAULT)
    {
      void *ptr = module_ctx->module_benchmark_esalt (hashconfig, user_options, user_options_extra);

      memcpy (hashes->esalts_buf, ptr, hashconfig->esalt_size);

      hcfree (ptr);
    }
    else
    {
      memcpy (hashes->esalts_buf, hashes->st_esalts_buf, hashconfig->esalt_size);
    }
  }

  if (hashconfig->hook_salt_size > 0)
  {
    if (module_ctx->module_benchmark_hook_salt != MODULE_DEFAULT)
    {
      void *ptr = module_ctx->module_benchmark_hook_salt (hashconfig, user_options, user_options_extra);

      memcpy (hashes->hook_salts_buf, ptr, hashconfig->hook_salt_size);

      hcfree (ptr);
    }
    else
    {
      memcpy (hashes->hook_salts_buf, hashes->st_hook_salts_buf, hashconfig->hook_salt_size);
    }
  }

  return 0;
}