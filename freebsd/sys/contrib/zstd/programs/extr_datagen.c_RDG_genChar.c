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
typedef  size_t U32 ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 size_t LTMASK ; 
 size_t RDG_rand (size_t*) ; 

__attribute__((used)) static BYTE RDG_genChar(U32* seed, const BYTE* ldt)
{
    U32 const id = RDG_rand(seed) & LTMASK;
    return ldt[id];  /* memory-sanitizer fails here, stating "uninitialized value" when table initialized with P==0.0. Checked : table is fully initialized */
}