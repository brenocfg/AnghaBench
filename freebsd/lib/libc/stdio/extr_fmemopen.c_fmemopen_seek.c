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
struct fmemopen_cookie {int size; int off; int len; } ;
typedef  int fpos_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static fpos_t
fmemopen_seek(void *cookie, fpos_t offset, int whence)
{
	struct fmemopen_cookie *ck = cookie;


	switch (whence) {
	case SEEK_SET:
		if (offset > ck->size) {
			errno = EINVAL;
			return (-1);
		}
		ck->off = offset;
		break;

	case SEEK_CUR:
		if (ck->off + offset > ck->size) {
			errno = EINVAL;
			return (-1);
		}
		ck->off += offset;
		break;

	case SEEK_END:
		if (offset > 0 || -offset > ck->len) {
			errno = EINVAL;
			return (-1);
		}
		ck->off = ck->len + offset;
		break;

	default:
		errno = EINVAL;
		return (-1);
	}

	return (ck->off);
}