#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t fileHandle_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int /*<<< orphan*/  z; } ;
struct TYPE_5__ {TYPE_1__ file; } ;
struct TYPE_6__ {scalar_t__ zipFile; long zipFileLen; TYPE_2__ handleFiles; int /*<<< orphan*/  zipFilePos; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int FS_FTell (size_t) ; 
 int /*<<< orphan*/ * FS_FileForHandle (size_t) ; 
 int /*<<< orphan*/  FS_Read (int /*<<< orphan*/ *,int,size_t) ; 
#define  FS_SEEK_CUR 130 
#define  FS_SEEK_END 129 
#define  FS_SEEK_SET 128 
 int PK3_SEEK_BUFFER_SIZE ; 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  fs_searchpaths ; 
 int fseek (int /*<<< orphan*/ *,long,int) ; 
 TYPE_3__* fsh ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  unzOpenCurrentFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unzSetOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int FS_Seek( fileHandle_t f, long offset, int origin ) {
	int		_origin;

	if ( !fs_searchpaths ) {
		Com_Error( ERR_FATAL, "Filesystem call made without initialization" );
		return -1;
	}

	if (fsh[f].zipFile == qtrue) {
		//FIXME: this is really, really crappy
		//(but better than what was here before)
		byte	buffer[PK3_SEEK_BUFFER_SIZE];
		int		remainder;
		int		currentPosition = FS_FTell( f );

		// change negative offsets into FS_SEEK_SET
		if ( offset < 0 ) {
			switch( origin ) {
				case FS_SEEK_END:
					remainder = fsh[f].zipFileLen + offset;
					break;

				case FS_SEEK_CUR:
					remainder = currentPosition + offset;
					break;

				case FS_SEEK_SET:
				default:
					remainder = 0;
					break;
			}

			if ( remainder < 0 ) {
				remainder = 0;
			}

			origin = FS_SEEK_SET;
		} else {
			if ( origin == FS_SEEK_END ) {
				remainder = fsh[f].zipFileLen - currentPosition + offset;
			} else {
				remainder = offset;
			}
		}

		switch( origin ) {
			case FS_SEEK_SET:
				if ( remainder == currentPosition ) {
					return offset;
				}
				unzSetOffset(fsh[f].handleFiles.file.z, fsh[f].zipFilePos);
				unzOpenCurrentFile(fsh[f].handleFiles.file.z);
				//fallthrough

			case FS_SEEK_END:
			case FS_SEEK_CUR:
				while( remainder > PK3_SEEK_BUFFER_SIZE ) {
					FS_Read( buffer, PK3_SEEK_BUFFER_SIZE, f );
					remainder -= PK3_SEEK_BUFFER_SIZE;
				}
				FS_Read( buffer, remainder, f );
				return offset;

			default:
				Com_Error( ERR_FATAL, "Bad origin in FS_Seek" );
				return -1;
		}
	} else {
		FILE *file;
		file = FS_FileForHandle(f);
		switch( origin ) {
		case FS_SEEK_CUR:
			_origin = SEEK_CUR;
			break;
		case FS_SEEK_END:
			_origin = SEEK_END;
			break;
		case FS_SEEK_SET:
			_origin = SEEK_SET;
			break;
		default:
			Com_Error( ERR_FATAL, "Bad origin in FS_Seek" );
			break;
		}

		return fseek( file, offset, _origin );
	}
}