#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*) ; 
 int hm_ADL_Adapter_NumberOfAdapters_Get (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int get_adapters_num_adl (hashcat_ctx_t *hashcat_ctx, int *iNumberAdapters)
{
  const int hm_rc = hm_ADL_Adapter_NumberOfAdapters_Get (hashcat_ctx, iNumberAdapters);

  if (hm_rc == -1) return -1;

  if (iNumberAdapters == NULL)
  {
    event_log_error (hashcat_ctx, "No ADL adapters found.");

    return -1;
  }

  return 0;
}