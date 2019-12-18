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
 int /*<<< orphan*/  ASSERT (int) ; 
 int CTF_VERSION ; 
 int MIN (int,int) ; 
 int _libctf_version ; 

int
ctf_version(int version)
{
	ASSERT(version > 0 && version <= CTF_VERSION);

	if (version > 0)
		_libctf_version = MIN(CTF_VERSION, version);

	return (_libctf_version);
}