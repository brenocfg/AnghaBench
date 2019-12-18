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
struct TYPE_3__ {size_t length; scalar_t__ data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static int
hex_to_octet_string(const char *ptr, krb5_data *data)
{
    size_t i;
    unsigned int v;
    for(i = 0; i < data->length; i++) {
	if(sscanf(ptr + 2 * i, "%02x", &v) != 1)
	    return -1;
	((unsigned char*)data->data)[i] = v;
    }
    return 2 * i;
}