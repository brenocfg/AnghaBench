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
typedef  int fsMode_t ;
typedef  int fileHandle_t ;
struct TYPE_2__ {int fileSize; int /*<<< orphan*/  handleSync; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
#define  FS_APPEND 131 
#define  FS_APPEND_SYNC 130 
 int FS_FOpenFileAppend (char const*) ; 
 int FS_FOpenFileRead (char const*,int*,int /*<<< orphan*/ ) ; 
 int FS_FOpenFileWrite (char const*) ; 
#define  FS_READ 129 
#define  FS_WRITE 128 
 TYPE_1__* fsh ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode ) {
	int		r;
	qboolean	sync;

	sync = qfalse;

	switch( mode ) {
		case FS_READ:
			r = FS_FOpenFileRead( qpath, f, qtrue );
			break;
		case FS_WRITE:
			*f = FS_FOpenFileWrite( qpath );
			r = 0;
			if (*f == 0) {
				r = -1;
			}
			break;
		case FS_APPEND_SYNC:
			sync = qtrue;
		case FS_APPEND:
			*f = FS_FOpenFileAppend( qpath );
			r = 0;
			if (*f == 0) {
				r = -1;
			}
			break;
		default:
			Com_Error( ERR_FATAL, "FS_FOpenFileByMode: bad mode" );
			return -1;
	}

	if (!f) {
		return r;
	}

	if ( *f ) {
		fsh[*f].fileSize = r;
	}
	fsh[*f].handleSync = sync;

	return r;
}