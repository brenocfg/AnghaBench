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
struct read_FILE_data {scalar_t__ can_skip; int /*<<< orphan*/  f; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  skip ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ _fseeki64 (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
file_skip(struct archive *a, void *client_data, int64_t request)
{
	struct read_FILE_data *mine = (struct read_FILE_data *)client_data;
#if HAVE_FSEEKO
	off_t skip = (off_t)request;
#elif HAVE__FSEEKI64
	int64_t skip = request;
#else
	long skip = (long)request;
#endif
	int skip_bits = sizeof(skip) * 8 - 1;

	(void)a; /* UNUSED */

	/*
	 * If we can't skip, return 0 as the amount we did step and
	 * the caller will work around by reading and discarding.
	 */
	if (!mine->can_skip)
		return (0);
	if (request == 0)
		return (0);

	/* If request is too big for a long or an off_t, reduce it. */
	if (sizeof(request) > sizeof(skip)) {
		int64_t max_skip =
		    (((int64_t)1 << (skip_bits - 1)) - 1) * 2 + 1;
		if (request > max_skip)
			skip = max_skip;
	}

#ifdef __ANDROID__
        /* fileno() isn't safe on all platforms ... see above. */
	if (lseek(fileno(mine->f), skip, SEEK_CUR) < 0)
#elif HAVE_FSEEKO
	if (fseeko(mine->f, skip, SEEK_CUR) != 0)
#elif HAVE__FSEEKI64
	if (_fseeki64(mine->f, skip, SEEK_CUR) != 0)
#else
	if (fseek(mine->f, skip, SEEK_CUR) != 0)
#endif
	{
		mine->can_skip = 0;
		return (0);
	}
	return (request);
}