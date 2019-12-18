#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void uint8_t ;
struct TYPE_3__ {size_t size; void* aligned; void* base; } ;
typedef  TYPE_1__ escrypt_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int MAP_ANON ; 
 void* MAP_FAILED ; 
 int MAP_NOCORE ; 
 int MAP_POPULATE ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_memalign (void**,int,size_t) ; 

void *
alloc_region(escrypt_region_t *region, size_t size)
{
    uint8_t *base, *aligned;
#if defined(MAP_ANON) && defined(HAVE_MMAP)
    if ((base = (uint8_t *) mmap(NULL, size, PROT_READ | PROT_WRITE,
                                 MAP_ANON | MAP_PRIVATE | MAP_NOCORE | MAP_POPULATE,
                                 -1, 0)) == MAP_FAILED) {
        base = NULL; /* LCOV_EXCL_LINE */
    }                /* LCOV_EXCL_LINE */
    aligned  = base;
#elif defined(HAVE_POSIX_MEMALIGN)
    if ((errno = posix_memalign((void **) &base, 64, size)) != 0) {
        base = NULL;
    }
    aligned = base;
#else
    base = aligned = NULL;
    if (size + 63 < size) {
        errno = ENOMEM;
    } else if ((base = (uint8_t *) malloc(size + 63)) != NULL) {
        aligned = base + 63;
        aligned -= (uintptr_t) aligned & 63;
    }
#endif
    region->base    = base;
    region->aligned = aligned;
    region->size    = base ? size : 0;

    return aligned;
}