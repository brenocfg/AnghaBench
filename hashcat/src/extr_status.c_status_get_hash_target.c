#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int (* module_hash_encode_status ) (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int const) ;} ;
typedef  TYPE_1__ module_ctx_t ;
struct TYPE_12__ {int digests_cnt; int /*<<< orphan*/ * hashfile; int /*<<< orphan*/  hook_salts_buf; int /*<<< orphan*/  esalts_buf; int /*<<< orphan*/  salts_buf; int /*<<< orphan*/  digests_buf; } ;
typedef  TYPE_2__ hashes_t ;
struct TYPE_13__ {int opts_type; } ;
typedef  TYPE_3__ hashconfig_t ;
struct TYPE_14__ {TYPE_1__* module_ctx; TYPE_2__* hashes; TYPE_3__* hashconfig; } ;
typedef  TYPE_4__ hashcat_ctx_t ;

/* Variables and functions */
 int const HCBUFSIZ_LARGE ; 
 int MODULE_DEFAULT (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int const) ; 
 int OPTS_TYPE_BINARY_HASHFILE ; 
 int /*<<< orphan*/  compress_terminal_line_length (char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hash_encode (TYPE_3__*,TYPE_2__*,TYPE_1__*,char*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hcmalloc (int const) ; 
 char* hcstrdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int const) ; 
 char* strdup (char*) ; 
 int stub1 (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int const) ; 

char *status_get_hash_target (const hashcat_ctx_t *hashcat_ctx)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;
  const hashes_t     *hashes     = hashcat_ctx->hashes;
  const module_ctx_t *module_ctx = hashcat_ctx->module_ctx;

  if ((hashes->digests_cnt == 1) || (hashes->hashfile == NULL))
  {
    if (module_ctx->module_hash_encode_status != MODULE_DEFAULT)
    {
      char *tmp_buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

      const int tmp_len = module_ctx->module_hash_encode_status (hashconfig, hashes->digests_buf, hashes->salts_buf, hashes->esalts_buf, hashes->hook_salts_buf, NULL, tmp_buf, HCBUFSIZ_LARGE);

      char *tmp_buf2 = (char *) hcmalloc (tmp_len + 1);

      memcpy (tmp_buf2, tmp_buf, tmp_len);

      tmp_buf2[tmp_len] = 0;

      free (tmp_buf);

      return tmp_buf2;
    }

    if (hashconfig->opts_type & OPTS_TYPE_BINARY_HASHFILE)
    {
      return hcstrdup (hashes->hashfile);
    }

    char *tmp_buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

    const int tmp_len = hash_encode (hashcat_ctx->hashconfig, hashcat_ctx->hashes, hashcat_ctx->module_ctx, tmp_buf, HCBUFSIZ_LARGE, 0, 0);

    tmp_buf[tmp_len] = 0;

    compress_terminal_line_length (tmp_buf, 19, 6); // 19 = strlen ("Hash.Target......: ")

    char *tmp_buf2 = strdup (tmp_buf);

    free (tmp_buf);

    return tmp_buf2;
  }

  return hcstrdup (hashes->hashfile);
}