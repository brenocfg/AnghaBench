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
struct timer_list {int dummy; } ;
struct img_ascii_lcd_ctx {unsigned int scroll_pos; unsigned int message_len; scalar_t__ scroll_rate; int /*<<< orphan*/  timer; TYPE_1__* cfg; int /*<<< orphan*/ * message; int /*<<< orphan*/ * curr; } ;
struct TYPE_2__ {unsigned int num_chars; int /*<<< orphan*/  (* update ) (struct img_ascii_lcd_ctx*) ;} ;

/* Variables and functions */
 struct img_ascii_lcd_ctx* ctx ; 
 struct img_ascii_lcd_ctx* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct img_ascii_lcd_ctx*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void img_ascii_lcd_scroll(struct timer_list *t)
{
	struct img_ascii_lcd_ctx *ctx = from_timer(ctx, t, timer);
	unsigned int i, ch = ctx->scroll_pos;
	unsigned int num_chars = ctx->cfg->num_chars;

	/* update the current message string */
	for (i = 0; i < num_chars;) {
		/* copy as many characters from the string as possible */
		for (; i < num_chars && ch < ctx->message_len; i++, ch++)
			ctx->curr[i] = ctx->message[ch];

		/* wrap around to the start of the string */
		ch = 0;
	}

	/* update the LCD */
	ctx->cfg->update(ctx);

	/* move on to the next character */
	ctx->scroll_pos++;
	ctx->scroll_pos %= ctx->message_len;

	/* rearm the timer */
	if (ctx->message_len > ctx->cfg->num_chars)
		mod_timer(&ctx->timer, jiffies + ctx->scroll_rate);
}