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
 size_t MAXRECSIZE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 
 size_t recbuf ; 
 size_t recpos ; 

__attribute__((used)) static int
record_buf(const void *buf, size_t size)
{

	if (MAXRECSIZE - recpos < size)
		errx(1, "record buffer overflow");
	memcpy(recbuf + recpos, buf, size);
	recpos += size;
	return (0);
}