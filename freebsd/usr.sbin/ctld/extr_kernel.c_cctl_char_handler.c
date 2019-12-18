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
struct cctl_devlist_data {size_t level; int /*<<< orphan*/ * cur_sb; } ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_bcat (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void
cctl_char_handler(void *user_data, const XML_Char *str, int len)
{
	struct cctl_devlist_data *devlist;

	devlist = (struct cctl_devlist_data *)user_data;

	sbuf_bcat(devlist->cur_sb[devlist->level], str, len);
}