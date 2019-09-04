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
struct TYPE_4__ {scalar_t__ digests_cnt; scalar_t__ digests_done; } ;
typedef  TYPE_1__ hashes_t ;
struct TYPE_5__ {TYPE_1__* hashes; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */

double status_get_digests_percent (const hashcat_ctx_t *hashcat_ctx)
{
  const hashes_t *hashes = hashcat_ctx->hashes;

  if (hashes->digests_cnt == 0) return 0;

  return ((double) hashes->digests_done / (double) hashes->digests_cnt) * 100;
}