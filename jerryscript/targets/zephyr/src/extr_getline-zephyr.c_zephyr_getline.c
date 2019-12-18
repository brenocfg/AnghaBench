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
struct console_input {char* line; } ;

/* Variables and functions */
 int /*<<< orphan*/  K_FOREVER ; 
 int /*<<< orphan*/  free_queue ; 
 struct console_input* k_fifo_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_fifo_put (int /*<<< orphan*/ *,struct console_input*) ; 
 int /*<<< orphan*/  used_queue ; 

char *zephyr_getline(void)
{
  static struct console_input *cmd;

  /* Recycle cmd buffer returned previous time */
  if (cmd != NULL)
  {
    k_fifo_put(&free_queue, cmd);
  }

  cmd = k_fifo_get(&used_queue, K_FOREVER);
  return cmd->line;
}