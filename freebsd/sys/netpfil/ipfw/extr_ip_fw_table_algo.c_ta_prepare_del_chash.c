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
struct tentry_info {int dummy; } ;
struct ta_buf_chash {int /*<<< orphan*/  ent; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int tei_to_chash_ent (struct tentry_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ta_prepare_del_chash(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_chash *tb;

	tb = (struct ta_buf_chash *)ta_buf;

	return (tei_to_chash_ent(tei, &tb->ent));
}