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
typedef  int /*<<< orphan*/  http_parser ;

/* Variables and functions */
 int /*<<< orphan*/ * current_pause_parser ; 
 int /*<<< orphan*/  http_parser_pause (int /*<<< orphan*/ *,int) ; 
 int message_complete_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  settings_dontcall ; 

int
pause_message_complete_cb (http_parser *p)
{
  http_parser_pause(p, 1);
  *current_pause_parser = settings_dontcall;
  return message_complete_cb(p);
}