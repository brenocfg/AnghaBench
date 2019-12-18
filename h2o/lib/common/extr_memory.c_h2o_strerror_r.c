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

/* Variables and functions */
 char* strerror_r (int,char*,size_t) ; 

char *h2o_strerror_r(int err, char *buf, size_t len)
{
#ifndef _GNU_SOURCE
    strerror_r(err, buf, len);
    return buf;
#else
    /**
     * The GNU-specific strerror_r() returns a pointer to a string containing the error message.
     * This may be either a pointer to a string that the function stores in  buf,
     * or a pointer to some (immutable) static string (in which case buf is unused)
     */
    return strerror_r(err, buf, len);
#endif
}