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
typedef  int u32 ;

/* Variables and functions */
 int OP_ALG_AAI_CMAC ; 
 int OP_ALG_AAI_MASK ; 
 int OP_ALG_ALGSEL_AES ; 
 int OP_ALG_ALGSEL_MASK ; 

__attribute__((used)) static inline bool is_cmac_aes(u32 algtype)
{
	return (algtype & (OP_ALG_ALGSEL_MASK | OP_ALG_AAI_MASK)) ==
	       (OP_ALG_ALGSEL_AES | OP_ALG_AAI_CMAC);
}