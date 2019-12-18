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
 int /*<<< orphan*/  CreatePath (char*) ; 
 int /*<<< orphan*/  FreeMemory (void*) ; 
 int LoadFile (char*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SaveFile (char*,void*,int) ; 

void QCopyFile (char *from, char *to)
{
	void	*buffer;
	int		length;

	length = LoadFile (from, &buffer, 0, 0);
	CreatePath (to);
	SaveFile (to, buffer, length);
	FreeMemory(buffer);
}