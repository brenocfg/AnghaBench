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
struct prompt {int active; int /*<<< orphan*/  logmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogMaskLocal ; 

void
log_ActivatePrompt(struct prompt *prompt)
{
  prompt->active = 1;
  LogMaskLocal |= prompt->logmask;
}