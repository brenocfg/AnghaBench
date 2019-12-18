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
struct mtk_sha_rec {struct mtk_cryp* cryp; } ;
struct mtk_cryp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_sha_complete (struct mtk_cryp*,struct mtk_sha_rec*) ; 
 int /*<<< orphan*/  mtk_sha_unmap (struct mtk_cryp*,struct mtk_sha_rec*) ; 

__attribute__((used)) static void mtk_sha_done_task(unsigned long data)
{
	struct mtk_sha_rec *sha = (struct mtk_sha_rec *)data;
	struct mtk_cryp *cryp = sha->cryp;

	mtk_sha_unmap(cryp, sha);
	mtk_sha_complete(cryp, sha);
}