#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_2__ {size_t nbBits; } ;
typedef  TYPE_1__ HUF_CElt ;

/* Variables and functions */
 size_t HUF_SYMBOLVALUE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

U32 HUF_getNbBits(const void* symbolTable, U32 symbolValue)
{
    const HUF_CElt* table = (const HUF_CElt*)symbolTable;
    assert(symbolValue <= HUF_SYMBOLVALUE_MAX);
    return table[symbolValue].nbBits;
}