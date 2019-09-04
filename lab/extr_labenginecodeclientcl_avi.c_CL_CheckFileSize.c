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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int fileSize; int numIndices; int /*<<< orphan*/  fileName; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_CloseAVI () ; 
 int /*<<< orphan*/  CL_OpenAVIForWriting (int /*<<< orphan*/ ) ; 
 unsigned int INT_MAX ; 
 TYPE_1__ afd ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static qboolean CL_CheckFileSize( int bytesToAdd )
{
  unsigned int newFileSize;

  newFileSize =
    afd.fileSize +                // Current file size
    bytesToAdd +                  // What we want to add
    ( afd.numIndices * 16 ) +     // The index
    4;                            // The index size

  // I assume all the operating systems
  // we target can handle a 2Gb file
  if( newFileSize > INT_MAX )
  {
    // Close the current file...
    CL_CloseAVI( );

    // ...And open a new one
    CL_OpenAVIForWriting( va( "%s_", afd.fileName ) );

    return qtrue;
  }

  return qfalse;
}