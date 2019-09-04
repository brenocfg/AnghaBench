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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FS_Remove (char const*) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int mkfifo (char const*,int) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 

FILE *Sys_Mkfifo( const char *ospath )
{
	FILE	*fifo;
	int	result;
	int	fn;
	struct	stat buf;

	// if file already exists AND is a pipefile, remove it
	if( !stat( ospath, &buf ) && S_ISFIFO( buf.st_mode ) )
		FS_Remove( ospath );

	result = mkfifo( ospath, 0600 );
	if( result != 0 )
		return NULL;

	fifo = fopen( ospath, "w+" );
	if( fifo )
	{
		fn = fileno( fifo );
		fcntl( fn, F_SETFL, O_NONBLOCK );
	}

	return fifo;
}