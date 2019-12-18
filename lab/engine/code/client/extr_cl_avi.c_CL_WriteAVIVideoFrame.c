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
typedef  int /*<<< orphan*/  const byte ;
struct TYPE_2__ {int fileSize; int moviOffset; int moviSize; int maxRecordSize; int /*<<< orphan*/  numIndices; int /*<<< orphan*/  idxF; int /*<<< orphan*/  numVideoFrames; int /*<<< orphan*/  f; int /*<<< orphan*/  fileOpen; } ;

/* Variables and functions */
 scalar_t__ CL_CheckFileSize (int) ; 
 int PADLEN (int,int) ; 
 int /*<<< orphan*/  SafeFS_Write (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_4BYTES (int) ; 
 int /*<<< orphan*/  WRITE_STRING (char*) ; 
 TYPE_1__ afd ; 
 scalar_t__ bufIndex ; 
 int /*<<< orphan*/  const* buffer ; 

void CL_WriteAVIVideoFrame( const byte *imageBuffer, int size )
{
  int   chunkOffset = afd.fileSize - afd.moviOffset - 8;
  int   chunkSize = 8 + size;
  int   paddingSize = PADLEN(size, 2);
  byte  padding[ 4 ] = { 0 };

  if( !afd.fileOpen )
    return;

  // Chunk header + contents + padding
  if( CL_CheckFileSize( 8 + size + 2 ) )
    return;

  bufIndex = 0;
  WRITE_STRING( "00dc" );
  WRITE_4BYTES( size );

  SafeFS_Write( buffer, 8, afd.f );
  SafeFS_Write( imageBuffer, size, afd.f );
  SafeFS_Write( padding, paddingSize, afd.f );
  afd.fileSize += ( chunkSize + paddingSize );

  afd.numVideoFrames++;
  afd.moviSize += ( chunkSize + paddingSize );

  if( size > afd.maxRecordSize )
    afd.maxRecordSize = size;

  // Index
  bufIndex = 0;
  WRITE_STRING( "00dc" );           //dwIdentifier
  WRITE_4BYTES( 0x00000010 );       //dwFlags (all frames are KeyFrames)
  WRITE_4BYTES( chunkOffset );      //dwOffset
  WRITE_4BYTES( size );             //dwLength
  SafeFS_Write( buffer, 16, afd.idxF );

  afd.numIndices++;
}