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
struct mtk_sha_rec {int dummy; } ;
struct mtk_cryp {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  mtk_sha_finish_req (struct mtk_cryp*,struct mtk_sha_rec*,int) ; 
 int mtk_sha_update_start (struct mtk_cryp*,struct mtk_sha_rec*) ; 

__attribute__((used)) static void mtk_sha_complete(struct mtk_cryp *cryp,
			     struct mtk_sha_rec *sha)
{
	int err = 0;

	err = mtk_sha_update_start(cryp, sha);
	if (err != -EINPROGRESS)
		mtk_sha_finish_req(cryp, sha, err);
}