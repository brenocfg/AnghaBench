#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t nbSlices; scalar_t__* capacities; } ;
typedef  TYPE_1__ slice_collection_t ;

/* Variables and functions */

__attribute__((used)) static size_t sliceCollection_totalCapacity(slice_collection_t sc)
{
    size_t totalSize = 0;
    for (size_t n=0; n<sc.nbSlices; n++)
        totalSize += sc.capacities[n];
    return totalSize;
}