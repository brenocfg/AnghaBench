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
typedef  int u8 ;
struct fsl_qdma_format {int cfg8b_w1; } ;

/* Variables and functions */
 int U8_MAX ; 

__attribute__((used)) static inline u8
qdma_ccdf_get_queue(const struct fsl_qdma_format *ccdf)
{
	return ccdf->cfg8b_w1 & U8_MAX;
}