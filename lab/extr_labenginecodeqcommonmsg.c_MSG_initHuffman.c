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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {int /*<<< orphan*/  decompressor; int /*<<< orphan*/  compressor; } ;

/* Variables and functions */
 int /*<<< orphan*/  Huff_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  Huff_addRef (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ msgHuff ; 
 int /*<<< orphan*/  msgInit ; 
 int* msg_hData ; 
 int /*<<< orphan*/  qtrue ; 

void MSG_initHuffman( void ) {
	int i,j;

	msgInit = qtrue;
	Huff_Init(&msgHuff);
	for(i=0;i<256;i++) {
		for (j=0;j<msg_hData[i];j++) {
			Huff_addRef(&msgHuff.compressor,	(byte)i);			// Do update
			Huff_addRef(&msgHuff.decompressor,	(byte)i);			// Do update
		}
	}
}