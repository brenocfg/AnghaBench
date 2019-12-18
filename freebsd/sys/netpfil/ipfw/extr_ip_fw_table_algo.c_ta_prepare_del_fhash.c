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
struct tentry_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  e; } ;
struct ta_buf_fhash {TYPE_1__ fe6; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int tei_to_fhash_ent (struct tentry_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ta_prepare_del_fhash(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_fhash *tb;

	tb = (struct ta_buf_fhash *)ta_buf;

	return (tei_to_fhash_ent(tei, &tb->fe6.e));
}