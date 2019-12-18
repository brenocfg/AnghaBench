#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  t_List ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * p_Lsts; } ;
typedef  TYPE_1__ t_EthHash ;

/* Variables and functions */
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 scalar_t__ XX_Malloc (int) ; 

__attribute__((used)) static __inline__ t_EthHash * AllocHashTable(uint16_t size)
{
    uint32_t    i;
    t_EthHash *p_Hash;

    /* Allocate address hash table */
    p_Hash = (t_EthHash *)XX_Malloc(sizeof(t_EthHash));
    if (!p_Hash)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("Address hash table"));
        return NULL;
    }
    p_Hash->size = size;

    p_Hash->p_Lsts = (t_List *)XX_Malloc(p_Hash->size*sizeof(t_List));
    if (!p_Hash->p_Lsts)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("Address hash table"));
        XX_Free(p_Hash);
        return NULL;
    }

    for (i=0 ; i<p_Hash->size; i++)
        INIT_LIST(&p_Hash->p_Lsts[i]);

    return p_Hash;
}