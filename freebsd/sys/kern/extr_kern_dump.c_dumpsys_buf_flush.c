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
struct dumperinfo {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  blockbuf; } ;

/* Variables and functions */
 int dump_append (struct dumperinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fragsz ; 

int
dumpsys_buf_flush(struct dumperinfo *di)
{
	int error;

	if (fragsz == 0)
		return (0);

	error = dump_append(di, di->blockbuf, 0, di->blocksize);
	fragsz = 0;
	return (error);
}