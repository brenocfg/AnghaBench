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
struct TYPE_3__ {size_t length; void* data; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int rk_undumpdata (char const*,void**,size_t*) ; 

int
_hx509_map_file_os(const char *fn, heim_octet_string *os)
{
    size_t length;
    void *data;
    int ret;

    ret = rk_undumpdata(fn, &data, &length);

    os->data = data;
    os->length = length;

    return ret;
}