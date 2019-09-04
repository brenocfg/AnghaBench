#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; scalar_t__ tag; struct TYPE_6__* next; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ memblock_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_10__ {int mark; int permanent; int temp; int tempHighwater; } ;
struct TYPE_9__ {int mark; int permanent; int temp; int tempHighwater; } ;
struct TYPE_8__ {TYPE_1__ blocklist; } ;
struct TYPE_7__ {TYPE_1__ blocklist; } ;

/* Variables and functions */
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 scalar_t__ TAG_BOTLIB ; 
 scalar_t__ TAG_RENDERER ; 
 TYPE_5__ hunk_high ; 
 TYPE_4__ hunk_low ; 
 TYPE_3__* mainzone ; 
 int s_hunkTotal ; 
 int s_zoneTotal ; 
 TYPE_2__* smallzone ; 

void Com_Meminfo_f( void ) {
	memblock_t	*block;
	int			zoneBytes, zoneBlocks;
	int			smallZoneBytes;
	int			botlibBytes, rendererBytes;
	int			unused;

	zoneBytes = 0;
	botlibBytes = 0;
	rendererBytes = 0;
	zoneBlocks = 0;
	for (block = mainzone->blocklist.next ; ; block = block->next) {
		if ( Cmd_Argc() != 1 ) {
			Com_Printf ("block:%p    size:%7i    tag:%3i\n",
				(void *)block, block->size, block->tag);
		}
		if ( block->tag ) {
			zoneBytes += block->size;
			zoneBlocks++;
			if ( block->tag == TAG_BOTLIB ) {
				botlibBytes += block->size;
			} else if ( block->tag == TAG_RENDERER ) {
				rendererBytes += block->size;
			}
		}

		if (block->next == &mainzone->blocklist) {
			break;			// all blocks have been hit	
		}
		if ( (byte *)block + block->size != (byte *)block->next) {
			Com_Printf ("ERROR: block size does not touch the next block\n");
		}
		if ( block->next->prev != block) {
			Com_Printf ("ERROR: next block doesn't have proper back link\n");
		}
		if ( !block->tag && !block->next->tag ) {
			Com_Printf ("ERROR: two consecutive free blocks\n");
		}
	}

	smallZoneBytes = 0;
	for (block = smallzone->blocklist.next ; ; block = block->next) {
		if ( block->tag ) {
			smallZoneBytes += block->size;
		}

		if (block->next == &smallzone->blocklist) {
			break;			// all blocks have been hit	
		}
	}

	Com_Printf( "%8i bytes total hunk\n", s_hunkTotal );
	Com_Printf( "%8i bytes total zone\n", s_zoneTotal );
	Com_Printf( "\n" );
	Com_Printf( "%8i low mark\n", hunk_low.mark );
	Com_Printf( "%8i low permanent\n", hunk_low.permanent );
	if ( hunk_low.temp != hunk_low.permanent ) {
		Com_Printf( "%8i low temp\n", hunk_low.temp );
	}
	Com_Printf( "%8i low tempHighwater\n", hunk_low.tempHighwater );
	Com_Printf( "\n" );
	Com_Printf( "%8i high mark\n", hunk_high.mark );
	Com_Printf( "%8i high permanent\n", hunk_high.permanent );
	if ( hunk_high.temp != hunk_high.permanent ) {
		Com_Printf( "%8i high temp\n", hunk_high.temp );
	}
	Com_Printf( "%8i high tempHighwater\n", hunk_high.tempHighwater );
	Com_Printf( "\n" );
	Com_Printf( "%8i total hunk in use\n", hunk_low.permanent + hunk_high.permanent );
	unused = 0;
	if ( hunk_low.tempHighwater > hunk_low.permanent ) {
		unused += hunk_low.tempHighwater - hunk_low.permanent;
	}
	if ( hunk_high.tempHighwater > hunk_high.permanent ) {
		unused += hunk_high.tempHighwater - hunk_high.permanent;
	}
	Com_Printf( "%8i unused highwater\n", unused );
	Com_Printf( "\n" );
	Com_Printf( "%8i bytes in %i zone blocks\n", zoneBytes, zoneBlocks	);
	Com_Printf( "        %8i bytes in dynamic botlib\n", botlibBytes );
	Com_Printf( "        %8i bytes in dynamic renderer\n", rendererBytes );
	Com_Printf( "        %8i bytes in dynamic other\n", zoneBytes - ( botlibBytes + rendererBytes ) );
	Com_Printf( "        %8i bytes in small Zone memory\n", smallZoneBytes );
}