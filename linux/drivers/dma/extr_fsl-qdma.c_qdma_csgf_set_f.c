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
struct fsl_qdma_format {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int QDMA_SG_FIN ; 
 int QDMA_SG_LEN_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline void qdma_csgf_set_f(struct fsl_qdma_format *csgf, int len)
{
	csgf->cfg = cpu_to_le32(QDMA_SG_FIN | (len & QDMA_SG_LEN_MASK));
}