#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int hlfmt_disable; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_8__ {TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  HCBUFSIZ_LARGE ; 
 scalar_t__ HLFMTS_CNT ; 
 scalar_t__ HLFMT_HASHCAT ; 
 size_t HLFMT_PASSWD ; 
 size_t HLFMT_PWDUMP ; 
 size_t HLFMT_SHADOW ; 
 size_t fgetl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  hc_feof (int /*<<< orphan*/ *) ; 
 scalar_t__ hccalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ hlfmt_detect_passwd (TYPE_2__*,char*,size_t const) ; 
 scalar_t__ hlfmt_detect_pwdump (TYPE_2__*,char*,size_t const) ; 
 scalar_t__ hlfmt_detect_shadow (TYPE_2__*,char*,size_t const) ; 

u32 hlfmt_detect (hashcat_ctx_t *hashcat_ctx, HCFILE *fp, u32 max_check)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

  // Exception: those formats are wrongly detected as HLFMT_SHADOW, prevent it

  if (hashconfig->hlfmt_disable == true) return HLFMT_HASHCAT;

  u32 *formats_cnt = (u32 *) hccalloc (HLFMTS_CNT, sizeof (u32));

  u32 num_check = 0;

  char *line_buf = (char *) hcmalloc (HCBUFSIZ_LARGE);

  while (!hc_feof (fp))
  {
    const size_t line_len = fgetl (fp, line_buf, HCBUFSIZ_LARGE);

    if (line_len == 0) continue;

    if (hlfmt_detect_pwdump (hashcat_ctx, line_buf, line_len)) formats_cnt[HLFMT_PWDUMP]++;
    if (hlfmt_detect_passwd (hashcat_ctx, line_buf, line_len)) formats_cnt[HLFMT_PASSWD]++;
    if (hlfmt_detect_shadow (hashcat_ctx, line_buf, line_len)) formats_cnt[HLFMT_SHADOW]++;

    if (num_check == max_check) break;

    num_check++;
  }

  hcfree (line_buf);

  u32 hashlist_format = HLFMT_HASHCAT;

  for (u32 i = 1; i < HLFMTS_CNT; i++)
  {
    if (formats_cnt[i - 1] >= formats_cnt[i]) continue;

    hashlist_format = i;
  }

  free (formats_cnt);

  return hashlist_format;
}