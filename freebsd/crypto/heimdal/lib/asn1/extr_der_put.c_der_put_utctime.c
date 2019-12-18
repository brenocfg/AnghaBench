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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int _heim_time2generalizedtime (int /*<<< orphan*/  const,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int der_put_octet_string (unsigned char*,size_t,TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

int
der_put_utctime (unsigned char *p, size_t len,
		 const time_t *data, size_t *size)
{
    heim_octet_string k;
    size_t l;
    int e;

    e = _heim_time2generalizedtime (*data, &k, 0);
    if (e)
	return e;
    e = der_put_octet_string(p, len, &k, &l);
    free(k.data);
    if(e)
	return e;
    if(size)
	*size = l;
    return 0;
}