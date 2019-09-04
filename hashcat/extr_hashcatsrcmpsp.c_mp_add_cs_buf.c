#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {int opts_type; } ;
typedef  TYPE_1__ hashconfig_t ;
struct TYPE_7__ {TYPE_1__* hashconfig; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
struct TYPE_8__ {size_t cs_len; size_t* cs_buf; } ;
typedef  TYPE_3__ cs_t ;

/* Variables and functions */
 int CHARSIZ ; 
 int OPTS_TYPE_PT_UPPER ; 
 int /*<<< orphan*/  hcfree (size_t*) ; 
 scalar_t__ hcmalloc (size_t) ; 
 scalar_t__ toupper (size_t) ; 

__attribute__((used)) static int mp_add_cs_buf (hashcat_ctx_t *hashcat_ctx, const u32 *in_buf, size_t in_len, cs_t *css, u32 css_cnt)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

  cs_t *cs = &css[css_cnt];

  size_t css_uniq_sz = CHARSIZ * sizeof (u32);

  u32 *css_uniq = (u32 *) hcmalloc (css_uniq_sz);

  size_t i;

  for (i = 0; i < cs->cs_len; i++)
  {
    const u32 u = cs->cs_buf[i];

    css_uniq[u] = 1;
  }

  for (i = 0; i < in_len; i++)
  {
    u32 u = in_buf[i] & 0xff;

    if (hashconfig->opts_type & OPTS_TYPE_PT_UPPER) u = (u32) toupper (u);

    if (css_uniq[u] == 1) continue;

    css_uniq[u] = 1;

    cs->cs_buf[cs->cs_len] = u;

    cs->cs_len++;
  }

  hcfree (css_uniq);

  return 0;
}