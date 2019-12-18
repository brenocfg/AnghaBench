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
struct prompt {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogSetMaskLocal () ; 

void
log_DeactivatePrompt(struct prompt *prompt)
{
  if (prompt->active) {
    prompt->active = 0;
    LogSetMaskLocal();
  }
}