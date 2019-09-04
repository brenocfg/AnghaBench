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

/* Variables and functions */
 int /*<<< orphan*/  BOTLIB_AI_GET_CHAT_MESSAGE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,char*,int) ; 

void trap_BotGetChatMessage(int chatstate, char *buf, int size) {
	syscall( BOTLIB_AI_GET_CHAT_MESSAGE, chatstate, buf, size);
}