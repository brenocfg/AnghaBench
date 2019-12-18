#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stat; } ;
struct nlm_res {TYPE_1__ stat; int /*<<< orphan*/  cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat; } ;
struct nlm4_res {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_convert_to_nlm_stats (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nlm_convert_to_nlm_res(struct nlm_res *dst, struct nlm4_res *src)
{
	dst->cookie = src->cookie;
	dst->stat.stat = nlm_convert_to_nlm_stats(src->stat.stat);
}