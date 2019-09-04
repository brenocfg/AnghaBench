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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* GetMemory (int) ; 
 int Q_filelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * SafeOpenRead (char*) ; 
 int /*<<< orphan*/  SafeRead (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int    LoadFile (char *filename, void **bufferptr, int offset, int length)
{
	FILE	*f;
	void    *buffer;

	f = SafeOpenRead(filename);
	fseek(f, offset, SEEK_SET);
	if (!length) length = Q_filelength(f);
	buffer = GetMemory(length+1);
	((char *)buffer)[length] = 0;
	SafeRead(f, buffer, length);
	fclose(f);

	*bufferptr = buffer;
	return length;
}