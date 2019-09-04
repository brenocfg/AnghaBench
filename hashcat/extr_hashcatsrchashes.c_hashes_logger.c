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
typedef  int /*<<< orphan*/  logfile_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  salts_done; int /*<<< orphan*/  salts_cnt; int /*<<< orphan*/  digests_done; int /*<<< orphan*/  digests_cnt; int /*<<< orphan*/  hashes_cnt; int /*<<< orphan*/  hashlist_format; int /*<<< orphan*/  hashlist_mode; int /*<<< orphan*/  hashfile; } ;
typedef  TYPE_1__ hashes_t ;
struct TYPE_5__ {int /*<<< orphan*/ * logfile_ctx; TYPE_1__* hashes; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  logfile_top_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile_top_uint (int /*<<< orphan*/ ) ; 

void hashes_logger (hashcat_ctx_t *hashcat_ctx)
{
  hashes_t      *hashes      = hashcat_ctx->hashes;
  logfile_ctx_t *logfile_ctx = hashcat_ctx->logfile_ctx;

  logfile_top_string (hashes->hashfile);
  logfile_top_uint   (hashes->hashlist_mode);
  logfile_top_uint   (hashes->hashlist_format);
  logfile_top_uint   (hashes->hashes_cnt);
  logfile_top_uint   (hashes->digests_cnt);
  logfile_top_uint   (hashes->digests_done);
  logfile_top_uint   (hashes->salts_cnt);
  logfile_top_uint   (hashes->salts_done);
}