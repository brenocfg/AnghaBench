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
typedef  int /*<<< orphan*/  fileHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  FS_SEEK_CUR ; 
 int /*<<< orphan*/  FS_Seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int PAD (int,int) ; 
 int /*<<< orphan*/  Q_strncmp (char*,char*,int) ; 
 int S_ReadChunkInfo (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int S_FindRIFFChunk( fileHandle_t f, char *chunk ) {
	char	name[5];
	int		len;

	while( ( len = S_ReadChunkInfo(f, name) ) >= 0 )
	{
		// If this is the right chunk, return
		if( !Q_strncmp( name, chunk, 4 ) )
			return len;

		len = PAD( len, 2 );

		// Not the right chunk - skip it
		FS_Seek( f, len, FS_SEEK_CUR );
	}

	return -1;
}