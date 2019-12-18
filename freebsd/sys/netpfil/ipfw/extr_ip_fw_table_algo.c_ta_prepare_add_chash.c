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
struct ta_buf_chash {struct chashentry* ent_ptr; } ;
struct ip_fw_chain {int dummy; } ;
struct chashentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW_TBL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct chashentry*,int /*<<< orphan*/ ) ; 
 struct chashentry* malloc (int,int /*<<< orphan*/ ,int) ; 
 int tei_to_chash_ent (struct tentry_info*,struct chashentry*) ; 

__attribute__((used)) static int
ta_prepare_add_chash(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_chash *tb;
	struct chashentry *ent;
	int error;

	tb = (struct ta_buf_chash *)ta_buf;

	ent = malloc(sizeof(*ent), M_IPFW_TBL, M_WAITOK | M_ZERO);

	error = tei_to_chash_ent(tei, ent);
	if (error != 0) {
		free(ent, M_IPFW_TBL);
		return (error);
	}
	tb->ent_ptr = ent;

	return (0);
}