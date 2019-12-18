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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_start; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_5__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 char* ctime_r (int /*<<< orphan*/  const*,char*) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 

char *status_get_time_started_absolute (const hashcat_ctx_t *hashcat_ctx)
{
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  const time_t time_start = status_ctx->runtime_start;

  char buf[32] = { 0 };

  char *start = ctime_r (&time_start, buf);

  const size_t start_len = strlen (start);

  if (start[start_len - 1] == '\n') start[start_len - 1] = 0;
  if (start[start_len - 2] == '\r') start[start_len - 2] = 0;

  return strdup (start);
}