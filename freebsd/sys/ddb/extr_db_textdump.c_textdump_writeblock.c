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
struct dumperinfo {scalar_t__ mediasize; scalar_t__ mediaoffset; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 scalar_t__ SIZEOF_METADATA ; 
 scalar_t__ TEXTDUMP_BLOCKSIZE ; 
 int dump_write (struct dumperinfo*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int) ; 
 int textdump_error ; 

__attribute__((used)) static int
textdump_writeblock(struct dumperinfo *di, off_t offset, char *buffer)
{

	if (textdump_error)
		return (textdump_error);
	if (offset + TEXTDUMP_BLOCKSIZE > di->mediasize)
		return (EIO);
	if (offset < SIZEOF_METADATA)
		return (ENOSPC);
	textdump_error = dump_write(di, buffer, 0, offset + di->mediaoffset,
	    TEXTDUMP_BLOCKSIZE);
	if (textdump_error)
		printf("textdump_writeblock: offset %jd, error %d\n", (intmax_t)offset,
		    textdump_error);
	return (textdump_error);
}