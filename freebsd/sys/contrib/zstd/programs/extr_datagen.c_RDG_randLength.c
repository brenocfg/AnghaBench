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
typedef  int U32 ;

/* Variables and functions */
 int RDG_rand (int*) ; 

__attribute__((used)) static U32 RDG_randLength(U32* seedPtr)
{
    if (RDG_rand(seedPtr) & 7) return (RDG_rand(seedPtr) & 0xF);   /* small length */
    return (RDG_rand(seedPtr) & 0x1FF) + 0xF;
}