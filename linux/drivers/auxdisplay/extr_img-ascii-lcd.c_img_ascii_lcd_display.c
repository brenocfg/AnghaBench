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
struct img_ascii_lcd_ctx {char* message; int message_len; int /*<<< orphan*/  timer; scalar_t__ scroll_pos; TYPE_1__* pdev; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,char*) ; 
 char* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ascii_lcd_scroll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int img_ascii_lcd_display(struct img_ascii_lcd_ctx *ctx,
			     const char *msg, ssize_t count)
{
	char *new_msg;

	/* stop the scroll timer */
	del_timer_sync(&ctx->timer);

	if (count == -1)
		count = strlen(msg);

	/* if the string ends with a newline, trim it */
	if (msg[count - 1] == '\n')
		count--;

	new_msg = devm_kmalloc(&ctx->pdev->dev, count + 1, GFP_KERNEL);
	if (!new_msg)
		return -ENOMEM;

	memcpy(new_msg, msg, count);
	new_msg[count] = 0;

	if (ctx->message)
		devm_kfree(&ctx->pdev->dev, ctx->message);

	ctx->message = new_msg;
	ctx->message_len = count;
	ctx->scroll_pos = 0;

	/* update the LCD */
	img_ascii_lcd_scroll(&ctx->timer);

	return 0;
}