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
struct fsl_qdma_format {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int QDMA_CCDF_MASK ; 
 int QDMA_CCDF_STATUS ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
qdma_ccdf_get_status(const struct fsl_qdma_format *ccdf)
{
	return (le32_to_cpu(ccdf->status) & QDMA_CCDF_MASK) >> QDMA_CCDF_STATUS;
}