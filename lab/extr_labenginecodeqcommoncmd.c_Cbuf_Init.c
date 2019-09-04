#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cursize; int /*<<< orphan*/  maxsize; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CMD_BUFFER ; 
 TYPE_1__ cmd_text ; 
 int /*<<< orphan*/  cmd_text_buf ; 

void Cbuf_Init (void)
{
	cmd_text.data = cmd_text_buf;
	cmd_text.maxsize = MAX_CMD_BUFFER;
	cmd_text.cursize = 0;
}