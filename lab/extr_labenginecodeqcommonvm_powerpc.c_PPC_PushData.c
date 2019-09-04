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
struct TYPE_4__ {long count; unsigned int* data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ local_data_t ;

/* Variables and functions */
 long LOCAL_DATA_CHUNK ; 
 TYPE_1__* PPC_Malloc (int) ; 
 size_t VM_Data_Offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * data ; 
 long data_acc ; 
 TYPE_1__* data_first ; 

__attribute__((used)) static size_t
PPC_PushData( unsigned int datum )
{
	local_data_t *d_now = data_first;
	long int accumulated = 0;

	// check whether we have this one already
	do {
		long int i;
		for ( i = 0; i < d_now->count; i++ ) {
			if ( d_now->data[ i ] == datum ) {
				accumulated += i;
				return VM_Data_Offset( data[ accumulated ] );
			}
		}
		if ( !d_now->next )
			break;

		accumulated += d_now->count;
		d_now = d_now->next;
	} while (1);

	// not found, need to append
	accumulated += d_now->count;

	// last chunk is full, create new one
	if ( d_now->count >= LOCAL_DATA_CHUNK ) {
		d_now->next = PPC_Malloc( sizeof( local_data_t ) );
		d_now = d_now->next;
		d_now->count = 0;
		d_now->next = NULL;
	}

	d_now->data[ d_now->count ] = datum;
	d_now->count += 1;

	data_acc = accumulated + 1;

	return VM_Data_Offset( data[ accumulated ] );
}