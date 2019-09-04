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
struct TYPE_4__ {int enabled; scalar_t__ induction_dictionaries_cnt; int /*<<< orphan*/  induction_dictionaries; int /*<<< orphan*/  root_directory; } ;
typedef  TYPE_1__ induct_ctx_t ;
struct TYPE_5__ {TYPE_1__* induct_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ count_dictionaries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_by_mtime ; 

void induct_ctx_scan (hashcat_ctx_t *hashcat_ctx)
{
  induct_ctx_t *induct_ctx = hashcat_ctx->induct_ctx;

  if (induct_ctx->enabled == false) return;

  induct_ctx->induction_dictionaries = scan_directory (induct_ctx->root_directory);

  induct_ctx->induction_dictionaries_cnt = count_dictionaries (induct_ctx->induction_dictionaries);

  qsort (induct_ctx->induction_dictionaries, (size_t) induct_ctx->induction_dictionaries_cnt, sizeof (char *), sort_by_mtime);
}