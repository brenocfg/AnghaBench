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
typedef  int /*<<< orphan*/  utmp ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int size; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_ITEM ;

/* Variables and functions */
 int INTxx_FLAG_SIGNED ; 
 int INTxx_FLAG_ZERO_DEFAULT ; 
 int i2c_uint64_int (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 

__attribute__((used)) static int uint64_i2c(ASN1_VALUE **pval, unsigned char *cont, int *putype,
                    const ASN1_ITEM *it)
{
    uint64_t utmp;
    int neg = 0;
    /* this exists to bypass broken gcc optimization */
    char *cp = (char *)*pval;

    /* use memcpy, because we may not be uint64_t aligned */
    memcpy(&utmp, cp, sizeof(utmp));

    if ((it->size & INTxx_FLAG_ZERO_DEFAULT) == INTxx_FLAG_ZERO_DEFAULT
        && utmp == 0)
        return -1;
    if ((it->size & INTxx_FLAG_SIGNED) == INTxx_FLAG_SIGNED
        && (int64_t)utmp < 0) {
        /* i2c_uint64_int() assumes positive values */
        utmp = 0 - utmp;
        neg = 1;
    }

    return i2c_uint64_int(cont, utmp, neg);
}