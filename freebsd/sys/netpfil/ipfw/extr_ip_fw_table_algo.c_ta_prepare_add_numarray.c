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
typedef  int /*<<< orphan*/  uint32_t ;
struct tentry_info {scalar_t__ paddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;
struct ta_buf_numarray {TYPE_1__ na; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
ta_prepare_add_numarray(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_numarray *tb;

	tb = (struct ta_buf_numarray *)ta_buf;

	tb->na.number = *((uint32_t *)tei->paddr);

	return (0);
}