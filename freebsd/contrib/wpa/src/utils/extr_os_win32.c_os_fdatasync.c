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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FlushFileBuffers (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 

int os_fdatasync(FILE *stream)
{
	HANDLE h;

	if (stream == NULL)
		return -1;

	h = (HANDLE) _get_osfhandle(_fileno(stream));
	if (h == INVALID_HANDLE_VALUE)
		return -1;

	if (!FlushFileBuffers(h))
		return -1;

	return 0;
}