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
struct TYPE_4__ {char open_mode; int compress_level; void* compressed_block; void* uncompressed_block; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  BGZF_MAX_BLOCK_SIZE ; 
 int Z_DEFAULT_COMPRESSION ; 
 TYPE_1__* calloc (int,int) ; 
 void* malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BGZF *bgzf_write_init(int compress_level) // compress_level==-1 for the default level
{
	BGZF *fp;
	fp = calloc(1, sizeof(BGZF));
	fp->open_mode = 'w';
	fp->uncompressed_block = malloc(BGZF_MAX_BLOCK_SIZE);
	fp->compressed_block = malloc(BGZF_MAX_BLOCK_SIZE);
	fp->compress_level = compress_level < 0? Z_DEFAULT_COMPRESSION : compress_level; // Z_DEFAULT_COMPRESSION==-1
	if (fp->compress_level > 9) fp->compress_level = Z_DEFAULT_COMPRESSION;
	return fp;
}