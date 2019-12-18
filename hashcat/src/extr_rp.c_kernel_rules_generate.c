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
struct TYPE_4__ {scalar_t__ rp_gen; int /*<<< orphan*/  rp_gen_func_max; int /*<<< orphan*/  rp_gen_func_min; } ;
typedef  TYPE_1__ user_options_t ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  kernel_rule_t ;
struct TYPE_5__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  RP_RULE_SIZE ; 
 int cpu_rule_to_kernel_rule (char*,int,int /*<<< orphan*/ *) ; 
 int generate_random_rule (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hccalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kernel_rules_generate (hashcat_ctx_t *hashcat_ctx, kernel_rule_t **out_buf, u32 *out_cnt)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  u32            kernel_rules_cnt = 0;
  kernel_rule_t *kernel_rules_buf = (kernel_rule_t *) hccalloc (user_options->rp_gen, sizeof (kernel_rule_t));

  char *rule_buf = (char *) hcmalloc (RP_RULE_SIZE);

  for (kernel_rules_cnt = 0; kernel_rules_cnt < user_options->rp_gen; kernel_rules_cnt++)
  {
    memset (rule_buf, 0, RP_RULE_SIZE);

    int rule_len = generate_random_rule (rule_buf, user_options->rp_gen_func_min, user_options->rp_gen_func_max);

    if (cpu_rule_to_kernel_rule (rule_buf, rule_len, &kernel_rules_buf[kernel_rules_cnt]) == -1) continue;
  }

  hcfree (rule_buf);

  *out_cnt = kernel_rules_cnt;
  *out_buf = kernel_rules_buf;

  return 0;
}