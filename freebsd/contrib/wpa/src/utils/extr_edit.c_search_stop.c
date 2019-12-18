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
 int /*<<< orphan*/  CMD_BUF_LEN ; 
 int /*<<< orphan*/  cmdbuf ; 
 int /*<<< orphan*/  cmdbuf_len ; 
 int /*<<< orphan*/  cmdbuf_pos ; 
 int /*<<< orphan*/  edit_redraw () ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ ) ; 
 char* search_buf ; 
 int /*<<< orphan*/  search_clear () ; 
 char* search_find () ; 

__attribute__((used)) static void search_stop(void)
{
	char *match = search_find();
	search_buf[0] = '\0';
	search_clear();
	if (match) {
		os_strlcpy(cmdbuf, match, CMD_BUF_LEN);
		cmdbuf_len = os_strlen(cmdbuf);
		cmdbuf_pos = cmdbuf_len;
	}
	edit_redraw();
}