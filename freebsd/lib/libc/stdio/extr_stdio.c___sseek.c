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
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ fpos_t ;
struct TYPE_2__ {int /*<<< orphan*/  _file; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

fpos_t
__sseek(void *cookie, fpos_t offset, int whence)
{
	FILE *fp = cookie;

	return (lseek(fp->_file, (off_t)offset, whence));
}