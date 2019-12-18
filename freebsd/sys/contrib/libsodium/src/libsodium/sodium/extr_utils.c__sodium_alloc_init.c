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
struct TYPE_3__ {scalar_t__ dwPageSize; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int CANARY_SIZE ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  canary ; 
 int page_size ; 
 int /*<<< orphan*/  randombytes_buf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sodium_misuse () ; 
 long sysconf (int /*<<< orphan*/ ) ; 

int
_sodium_alloc_init(void)
{
#ifdef HAVE_ALIGNED_MALLOC
# if defined(_SC_PAGESIZE)
    long page_size_ = sysconf(_SC_PAGESIZE);
    if (page_size_ > 0L) {
        page_size = (size_t) page_size_;
    }
# elif defined(WINAPI_DESKTOP)
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    page_size = (size_t) si.dwPageSize;
# endif
    if (page_size < CANARY_SIZE || page_size < sizeof(size_t)) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
#endif
    randombytes_buf(canary, sizeof canary);

    return 0;
}