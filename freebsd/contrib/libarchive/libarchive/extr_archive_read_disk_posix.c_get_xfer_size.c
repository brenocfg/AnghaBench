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
struct tree {TYPE_1__* current_filesystem; } ;
struct TYPE_2__ {int xfer_align; void* min_xfer_size; void* max_xfer_size; void* incr_xfer_size; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  _PC_REC_INCR_XFER_SIZE ; 
 int /*<<< orphan*/  _PC_REC_MAX_XFER_SIZE ; 
 int /*<<< orphan*/  _PC_REC_MIN_XFER_SIZE ; 
 int /*<<< orphan*/  _PC_REC_XFER_ALIGN ; 
 scalar_t__ errno ; 
 void* fpathconf (int,int /*<<< orphan*/ ) ; 
 void* pathconf (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_xfer_size(struct tree *t, int fd, const char *path)
{
	t->current_filesystem->xfer_align = -1;
	errno = 0;
	if (fd >= 0) {
		t->current_filesystem->incr_xfer_size =
		    fpathconf(fd, _PC_REC_INCR_XFER_SIZE);
		t->current_filesystem->max_xfer_size =
		    fpathconf(fd, _PC_REC_MAX_XFER_SIZE);
		t->current_filesystem->min_xfer_size =
		    fpathconf(fd, _PC_REC_MIN_XFER_SIZE);
		t->current_filesystem->xfer_align =
		    fpathconf(fd, _PC_REC_XFER_ALIGN);
	} else if (path != NULL) {
		t->current_filesystem->incr_xfer_size =
		    pathconf(path, _PC_REC_INCR_XFER_SIZE);
		t->current_filesystem->max_xfer_size =
		    pathconf(path, _PC_REC_MAX_XFER_SIZE);
		t->current_filesystem->min_xfer_size =
		    pathconf(path, _PC_REC_MIN_XFER_SIZE);
		t->current_filesystem->xfer_align =
		    pathconf(path, _PC_REC_XFER_ALIGN);
	}
	/* At least we need an alignment size. */
	if (t->current_filesystem->xfer_align == -1)
		return ((errno == EINVAL)?1:-1);
	else
		return (0);
}