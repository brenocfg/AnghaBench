#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  scalar_t__ off_t ;
typedef  TYPE_1__* mpcth_t ;
typedef  int intmax_t ;
struct TYPE_8__ {int base_table_length; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPCTH_SIG ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memread (scalar_t__,TYPE_1__*,int) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static mpcth_t
biosmptable_check_mpcth(off_t addr)
{
    mpcth_t mpcth;
    u_int8_t *cp, sum;
    int idx, table_length;

    /* mpcth must be in the first 1MB */
    if ((u_int32_t)addr >= 1024 * 1024) {
	warnx("bad mpcth address (0x%jx)\n", (intmax_t)addr);
	return (NULL);
    }

    mpcth = malloc(sizeof(*mpcth));
    if (mpcth == NULL) {
	warnx("unable to malloc space for MP Configuration Table Header");
	return (NULL);
    }
    if (!memread(addr, mpcth, sizeof(*mpcth)))
	goto bad;
    /* Compare signature and validate checksum. */
    if (strncmp(mpcth->signature, MPCTH_SIG, strlen(MPCTH_SIG)) != 0) {
        warnx("bad mpcth signature");
	goto bad;
    }
    table_length = mpcth->base_table_length;
    mpcth = realloc(mpcth, table_length);
    if (mpcth == NULL) {
	warnx("unable to realloc space for mpcth (len %u)", table_length);
	return  (NULL);
    }
    if (!memread(addr, mpcth, table_length))
	goto bad;
    cp = (u_int8_t *)mpcth;
    sum = 0;
    for (idx = 0; idx < mpcth->base_table_length; idx++)
	sum += *(cp + idx);
    if (sum != 0) {
	warnx("bad mpcth checksum (%d)", sum);
	goto bad;
    }

    return mpcth;
bad:
    free(mpcth);
    return (NULL);
}