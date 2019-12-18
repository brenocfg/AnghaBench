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
struct rsocket {int dummy; } ;

/* Variables and functions */
 scalar_t__ rs_give_credits (struct rsocket*) ; 
 int /*<<< orphan*/  rs_send_credits (struct rsocket*) ; 

__attribute__((used)) static void rs_update_credits(struct rsocket *rs)
{
	if (rs_give_credits(rs))
		rs_send_credits(rs);
}