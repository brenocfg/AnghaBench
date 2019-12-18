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
typedef  int u64 ;
struct fsl_qdma_format {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int U64_MAX ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64
qdma_ccdf_addr_get64(const struct fsl_qdma_format *ccdf)
{
	return le64_to_cpu(ccdf->data) & (U64_MAX >> 24);
}