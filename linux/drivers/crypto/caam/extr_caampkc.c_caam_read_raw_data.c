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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  caam_rsa_drop_leading_zeros (int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,size_t,int) ; 

__attribute__((used)) static inline u8 *caam_read_raw_data(const u8 *buf, size_t *nbytes)
{

	caam_rsa_drop_leading_zeros(&buf, nbytes);
	if (!*nbytes)
		return NULL;

	return kmemdup(buf, *nbytes, GFP_DMA | GFP_KERNEL);
}