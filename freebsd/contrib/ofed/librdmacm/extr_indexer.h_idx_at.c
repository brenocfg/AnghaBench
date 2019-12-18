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
struct indexer {TYPE_1__** array; } ;
struct TYPE_2__ {void* item; } ;

/* Variables and functions */
 size_t idx_array_index (int) ; 
 int idx_entry_index (int) ; 

__attribute__((used)) static inline void *idx_at(struct indexer *idx, int index)
{
	return (idx->array[idx_array_index(index)] + idx_entry_index(index))->item;
}