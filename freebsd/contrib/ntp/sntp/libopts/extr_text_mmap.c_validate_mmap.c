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
struct TYPE_4__ {scalar_t__ txt_fd; int txt_prot; int txt_flags; size_t txt_size; void* txt_errno; scalar_t__ txt_zero_fd; } ;
typedef  TYPE_1__ tmap_info_t ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ AO_INVALID_FD ; 
 void* EINVAL ; 
 scalar_t__ FILE_WRITABLE (int,int) ; 
 int MAP_SHARED ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 void* errno ; 
 scalar_t__ fstat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ open (char const*,int) ; 

__attribute__((used)) static void
validate_mmap(char const * fname, int prot, int flags, tmap_info_t * mapinfo)
{
    memset(mapinfo, 0, sizeof(*mapinfo));
#if defined(HAVE_MMAP) && ! defined(MAP_ANONYMOUS)
    mapinfo->txt_zero_fd = AO_INVALID_FD;
#endif
    mapinfo->txt_fd      = AO_INVALID_FD;
    mapinfo->txt_prot    = prot;
    mapinfo->txt_flags   = flags;

    /*
     *  Map mmap flags and protections into open flags and do the open.
     */
    {
        /*
         *  See if we will be updating the file.  If we can alter the memory
         *  and if we share the data and we are *not* copy-on-writing the data,
         *  then our updates will show in the file, so we must open with
         *  write access.
         */
        int o_flag = FILE_WRITABLE(prot, flags) ? O_RDWR : O_RDONLY;

        /*
         *  If you're not sharing the file and you are writing to it,
         *  then don't let anyone else have access to the file.
         */
        if (((flags & MAP_SHARED) == 0) && (prot & PROT_WRITE))
            o_flag |= O_EXCL;

        mapinfo->txt_fd = open(fname, o_flag);
        if (mapinfo->txt_fd < 0) {
            mapinfo->txt_errno = errno;
            mapinfo->txt_fd = AO_INVALID_FD;
            return;
        }
    }

    /*
     *  Make sure we can stat the regular file.  Save the file size.
     */
    {
        struct stat sb;
        if (fstat(mapinfo->txt_fd, &sb) != 0) {
            mapinfo->txt_errno = errno;
            close(mapinfo->txt_fd);
            return;
        }

        if (! S_ISREG(sb.st_mode)) {
            mapinfo->txt_errno = errno = EINVAL;
            close(mapinfo->txt_fd);
            return;
        }

        mapinfo->txt_size = (size_t)sb.st_size;
    }

    if (mapinfo->txt_fd == AO_INVALID_FD)
        mapinfo->txt_errno = errno;
}