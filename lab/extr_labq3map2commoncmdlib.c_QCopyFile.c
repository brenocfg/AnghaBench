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

/* Variables and functions */
 int /*<<< orphan*/  CreatePath (char const*) ; 
 int LoadFile (char const*,void**) ; 
 int /*<<< orphan*/  SaveFile (char const*,void*,int) ; 
 int /*<<< orphan*/  free (void*) ; 

void QCopyFile( const char *from, const char *to ){
	void    *buffer;
	int length;

	length = LoadFile( from, &buffer );
	CreatePath( to );
	SaveFile( to, buffer, length );
	free( buffer );
}