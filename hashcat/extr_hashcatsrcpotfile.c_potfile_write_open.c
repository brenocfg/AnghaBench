#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enabled; int /*<<< orphan*/ * fp; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ potfile_ctx_t ;
struct TYPE_6__ {TYPE_1__* potfile_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int potfile_write_open (hashcat_ctx_t *hashcat_ctx)
{
  potfile_ctx_t *potfile_ctx = hashcat_ctx->potfile_ctx;

  if (potfile_ctx->enabled == false) return 0;

  FILE *fp = fopen (potfile_ctx->filename, "ab");

  if (fp == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", potfile_ctx->filename, strerror (errno));

    return -1;
  }

  potfile_ctx->fp = fp;

  return 0;
}