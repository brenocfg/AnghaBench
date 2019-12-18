#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ txt_errno; void* txt_data; } ;
typedef  TYPE_1__ tmap_info_t ;

/* Variables and functions */
 void* MAP_FAILED_PTR ; 
 int /*<<< orphan*/  close_mmap_files (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  load_text_file (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  validate_mmap (char const*,int,int,TYPE_1__*) ; 

void *
text_mmap(char const * pzFile, int prot, int flags, tmap_info_t * mi)
{
    validate_mmap(pzFile, prot, flags, mi);
    if (mi->txt_errno != 0)
        return MAP_FAILED_PTR;

    load_text_file(mi, pzFile);

    if (mi->txt_errno == 0)
        return mi->txt_data;

    close_mmap_files(mi);

    errno = mi->txt_errno;
    mi->txt_data = MAP_FAILED_PTR;
    return mi->txt_data;
}