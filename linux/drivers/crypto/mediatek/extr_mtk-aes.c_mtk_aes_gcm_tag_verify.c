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
typedef  int u32 ;
struct mtk_cryp {TYPE_2__** ring; } ;
struct mtk_aes_rec {size_t id; } ;
struct TYPE_4__ {TYPE_1__* res_prev; } ;
struct TYPE_3__ {int ct; } ;

/* Variables and functions */
 int AES_AUTH_TAG_ERR ; 
 int /*<<< orphan*/  EBADMSG ; 
 int mtk_aes_complete (struct mtk_cryp*,struct mtk_aes_rec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_aes_gcm_tag_verify(struct mtk_cryp *cryp,
				  struct mtk_aes_rec *aes)
{
	u32 status = cryp->ring[aes->id]->res_prev->ct;

	return mtk_aes_complete(cryp, aes, (status & AES_AUTH_TAG_ERR) ?
				-EBADMSG : 0);
}