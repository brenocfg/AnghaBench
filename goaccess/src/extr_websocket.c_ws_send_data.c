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
typedef  int /*<<< orphan*/  WSOpcode ;
typedef  int /*<<< orphan*/  WSClient ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* sanitize_utf8 (char const*,int) ; 
 int /*<<< orphan*/  ws_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

int
ws_send_data (WSClient * client, WSOpcode opcode, const char *p, int sz)
{
  char *buf = NULL;

  buf = sanitize_utf8 (p, sz);
  ws_send_frame (client, opcode, buf, sz);
  free (buf);

  return 0;
}