#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_12__ {size_t const digests_offset; } ;
typedef  TYPE_1__ salt_t ;
struct TYPE_13__ {int (* module_hash_encode ) (TYPE_4__ const*,char*,TYPE_1__*,char*,char*,int /*<<< orphan*/ *,char*,int const) ;} ;
typedef  TYPE_2__ module_ctx_t ;
typedef  int /*<<< orphan*/  hashinfo_t ;
struct TYPE_14__ {char* hashfile; int /*<<< orphan*/ ** hash_info; void* hook_salts_buf; void* esalts_buf; void* digests_buf; TYPE_1__* salts_buf; } ;
typedef  TYPE_3__ hashes_t ;
struct TYPE_15__ {size_t const dgst_size; size_t const esalt_size; size_t const hook_salt_size; } ;
typedef  TYPE_4__ hashconfig_t ;

/* Variables and functions */
 int MODULE_DEFAULT (TYPE_4__ const*,char*,TYPE_1__*,char*,char*,int /*<<< orphan*/ *,char*,int const) ; 
 int snprintf (char*,int const,char*,char*) ; 
 int stub1 (TYPE_4__ const*,char*,TYPE_1__*,char*,char*,int /*<<< orphan*/ *,char*,int const) ; 

int hash_encode (const hashconfig_t *hashconfig, const hashes_t *hashes, const module_ctx_t *module_ctx, char *out_buf, const int out_size, const u32 salt_pos, const u32 digest_pos)
{
  if (module_ctx->module_hash_encode == MODULE_DEFAULT)
  {
    return snprintf (out_buf, out_size, "%s", hashes->hashfile);
  }

  salt_t *salts_buf = hashes->salts_buf;

  salts_buf += salt_pos;

  const u32 digest_cur = salts_buf->digests_offset + digest_pos;

  void        *digests_buf    = hashes->digests_buf;
  void        *esalts_buf     = hashes->esalts_buf;
  void        *hook_salts_buf = hashes->hook_salts_buf;
  hashinfo_t **hash_info      = hashes->hash_info;

  char       *digests_buf_ptr    = (char *) digests_buf;
  char       *esalts_buf_ptr     = (char *) esalts_buf;
  char       *hook_salts_buf_ptr = (char *) hook_salts_buf;
  hashinfo_t *hash_info_ptr      = NULL;

  digests_buf_ptr    += digest_cur * hashconfig->dgst_size;
  esalts_buf_ptr     += digest_cur * hashconfig->esalt_size;
  hook_salts_buf_ptr += digest_cur * hashconfig->hook_salt_size;

  if (hash_info) hash_info_ptr = hash_info[digest_cur];

  const int out_len = module_ctx->module_hash_encode
  (
    hashconfig,
    digests_buf_ptr,
    salts_buf,
    esalts_buf_ptr,
    hook_salts_buf_ptr,
    hash_info_ptr,
    out_buf,
    out_size
  );

  return out_len;
}