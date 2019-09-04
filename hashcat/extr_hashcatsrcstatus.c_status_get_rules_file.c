#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rp_files_cnt; char** rp_files; } ;
typedef  TYPE_1__ user_options_t ;
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ HCBUFSIZ_TINY ; 
 scalar_t__ hcmalloc (scalar_t__) ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,char*) ; 

__attribute__((used)) static char *status_get_rules_file (const hashcat_ctx_t *hashcat_ctx)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->rp_files_cnt > 0)
  {
    char *tmp_buf = (char *) hcmalloc (HCBUFSIZ_TINY);

    int tmp_len = 0;

    u32 i;

    for (i = 0; i < user_options->rp_files_cnt - 1; i++)
    {
      tmp_len += snprintf (tmp_buf + tmp_len, HCBUFSIZ_TINY - tmp_len, "%s, ", user_options->rp_files[i]);
    }

    tmp_len += snprintf (tmp_buf + tmp_len, HCBUFSIZ_TINY - tmp_len, "%s", user_options->rp_files[i]);

    tmp_buf[tmp_len] = 0;

    return tmp_buf; // yes, user need to free()
  }

  return NULL;
}