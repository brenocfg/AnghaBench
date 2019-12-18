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
struct unicx {scalar_t__ errcnt; } ;
struct uni_msg {int dummy; } ;
struct uni_all {int dummy; } ;

/* Variables and functions */
 scalar_t__ uni_decode_body (struct uni_msg*,struct uni_all*,struct unicx*) ; 
 scalar_t__ uni_decode_head (struct uni_msg*,struct uni_all*,struct unicx*) ; 

int
uni_decode(struct uni_msg *msg, struct uni_all *out, struct unicx *cx)
{
	cx->errcnt = 0;
	if (uni_decode_head(msg, out, cx))
		return (-1);
	if (uni_decode_body(msg, out, cx))
		return (-2);
	return (0);
}