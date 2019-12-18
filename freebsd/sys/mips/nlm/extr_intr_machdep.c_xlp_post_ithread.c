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
struct xlp_intrsrc {int /*<<< orphan*/  irt; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_pic_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_pic_base ; 

__attribute__((used)) static void
xlp_post_ithread(void *source)
{
	struct xlp_intrsrc *src = source;

	nlm_pic_ack(xlp_pic_base, src->irt);
}