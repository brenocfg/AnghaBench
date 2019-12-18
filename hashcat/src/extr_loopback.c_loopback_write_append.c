#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int enabled; int unused; int /*<<< orphan*/  filename; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ loopback_ctx_t ;
struct TYPE_7__ {TYPE_1__* loopback_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOL ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_lockfile (int /*<<< orphan*/ *) ; 
 scalar_t__ hc_unlockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loopback_format_plain (TYPE_2__*,int /*<<< orphan*/  const*,unsigned int const) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void loopback_write_append (hashcat_ctx_t *hashcat_ctx, const u8 *plain_ptr, const unsigned int plain_len)
{
  loopback_ctx_t *loopback_ctx = hashcat_ctx->loopback_ctx;

  if (loopback_ctx->enabled == false) return;

  loopback_format_plain (hashcat_ctx, plain_ptr, plain_len);

  hc_lockfile (&loopback_ctx->fp);

  hc_fwrite (EOL, strlen (EOL), 1, &loopback_ctx->fp);

  hc_fflush (&loopback_ctx->fp);

  if (hc_unlockfile (&loopback_ctx->fp))
  {
    event_log_error (hashcat_ctx, "%s: Failed to unlock file", loopback_ctx->filename);
  }

  loopback_ctx->unused = false;
}