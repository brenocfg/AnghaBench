#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int txt_errno; int /*<<< orphan*/  txt_data; int /*<<< orphan*/  txt_size; int /*<<< orphan*/  txt_fd; int /*<<< orphan*/  txt_flags; int /*<<< orphan*/  txt_prot; int /*<<< orphan*/  txt_full_size; } ;
typedef  TYPE_1__ tmap_info_t ;

/* Variables and functions */
 scalar_t__ FILE_WRITABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close_mmap_files (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
text_munmap(tmap_info_t * mi)
{
    errno = 0;

#ifdef HAVE_MMAP
    (void)munmap(mi->txt_data, mi->txt_full_size);

#else  /* don't HAVE_MMAP */
    /*
     *  IF the memory is writable *AND* it is not private (copy-on-write)
     *     *AND* the memory is "sharable" (seen by other processes)
     *  THEN rewrite the data.  Emulate mmap visibility.
     */
    if (   FILE_WRITABLE(mi->txt_prot, mi->txt_flags)
        && (lseek(mi->txt_fd, 0, SEEK_SET) >= 0) ) {
        write(mi->txt_fd, mi->txt_data, mi->txt_size);
    }

    free(mi->txt_data);
#endif /* HAVE_MMAP */

    mi->txt_errno = errno;
    close_mmap_files(mi);

    return mi->txt_errno;
}