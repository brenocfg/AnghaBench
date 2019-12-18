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
typedef  unsigned int uint64_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sodium_misuse () ; 

__attribute__((used)) static uint64_t
sodium_hrtime(void)
{
    struct   timeval tv;

    if (gettimeofday(&tv, NULL) != 0) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
    return ((uint64_t) tv.tv_sec) * 1000000U + (uint64_t) tv.tv_usec;
}