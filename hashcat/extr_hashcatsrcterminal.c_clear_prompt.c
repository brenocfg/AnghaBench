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
struct TYPE_4__ {scalar_t__ devices_status; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_5__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROMPT_ACTIVE ; 
 int /*<<< orphan*/  PROMPT_PAUSED ; 
 scalar_t__ STATUS_PAUSED ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

void clear_prompt (hashcat_ctx_t *hashcat_ctx)
{
  const status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  size_t prompt_sz = 0;

  if (status_ctx->devices_status == STATUS_PAUSED)
  {
    prompt_sz = strlen (PROMPT_PAUSED);
  }
  else
  {
    prompt_sz = strlen (PROMPT_ACTIVE);
  }

  fputc ('\r', stdout);

  for (size_t i = 0; i < prompt_sz; i++)
  {
    fputc (' ', stdout);
  }

  fputc ('\r', stdout);

  fflush (stdout);
}