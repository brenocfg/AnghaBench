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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOUNDARY_SIZE ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_memis (char*,int,char const*,...) ; 

__attribute__((used)) static int check_multirange_body(char *resbody, const char *boundary, const h2o_iovec_t *expected, size_t partlen)
{
    char *bptr = resbody;
    const h2o_iovec_t *eptr = expected;
    int not_first_line = 0;
    while (partlen--) {
        if (not_first_line) {
            if (!h2o_memis(bptr, 2, H2O_STRLIT("\r\n")))
                return 0;
            bptr += 2;
        } else
            not_first_line = 1;
        if (!h2o_memis(bptr, 2, H2O_STRLIT("--")))
            return 0;
        bptr += 2;
        if (!h2o_memis(bptr, BOUNDARY_SIZE, boundary, BOUNDARY_SIZE))
            return 0;
        bptr += 20;
        if (!h2o_memis(bptr, 2, H2O_STRLIT("\r\n")))
            return 0;
        bptr += 2;
        if (!h2o_memis(bptr, eptr->len, eptr->base, eptr->len))
            return 0;
        bptr += eptr->len;
        eptr++;
    }
    if (!h2o_memis(bptr, 4, H2O_STRLIT("\r\n--")))
        return 0;
    bptr += 4;
    if (!h2o_memis(bptr, BOUNDARY_SIZE, boundary, BOUNDARY_SIZE))
        return 0;
    bptr += 20;
    if (!h2o_memis(bptr, 4, H2O_STRLIT("--\r\n")))
        return 0;
    return 1;
}