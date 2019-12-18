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
struct prompt {struct prompt* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogSetMaskLocal () ; 
 int /*<<< orphan*/  log_PromptListChanged ; 
 struct prompt* promptlist ; 

void
log_UnRegisterPrompt(struct prompt *prompt)
{
  if (prompt) {
    struct prompt **p;

    for (p = &promptlist; *p; p = &(*p)->next)
      if (*p == prompt) {
        *p = prompt->next;
        prompt->next = NULL;
        break;
      }
    LogSetMaskLocal();
    log_PromptListChanged++;
  }
}