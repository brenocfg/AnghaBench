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
 int OP_ALG_ALGSEL_MASK ; 
 int OP_ALG_ALGSEL_SUBMASK ; 
 int OP_ALG_CHA_MDHA ; 

__attribute__((used)) static inline bool is_mdha(u32 algtype)
{
	return (algtype & OP_ALG_ALGSEL_MASK & ~OP_ALG_ALGSEL_SUBMASK) ==
	       OP_ALG_CHA_MDHA;
}