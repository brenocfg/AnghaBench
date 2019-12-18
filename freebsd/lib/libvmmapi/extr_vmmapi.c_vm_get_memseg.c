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
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_memseg {int segid; size_t len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  VM_GET_MEMSEG ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_memseg*) ; 
 size_t strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

int
vm_get_memseg(struct vmctx *ctx, int segid, size_t *lenp, char *namebuf,
    size_t bufsize)
{
	struct vm_memseg memseg;
	size_t n;
	int error;

	memseg.segid = segid;
	error = ioctl(ctx->fd, VM_GET_MEMSEG, &memseg);
	if (error == 0) {
		*lenp = memseg.len;
		n = strlcpy(namebuf, memseg.name, bufsize);
		if (n >= bufsize) {
			errno = ENAMETOOLONG;
			error = -1;
		}
	}
	return (error);
}