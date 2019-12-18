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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int /*<<< orphan*/  _heim_time2generalizedtime (int /*<<< orphan*/  const,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

size_t
der_length_generalized_time (const time_t *t)
{
    heim_octet_string k;
    size_t ret;

    _heim_time2generalizedtime (*t, &k, 1);
    ret = k.length;
    free(k.data);
    return ret;
}