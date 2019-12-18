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
struct _krb5_checksum_type {scalar_t__ type; } ;
typedef  scalar_t__ krb5_cksumtype ;

/* Variables and functions */
 struct _krb5_checksum_type** _krb5_checksum_types ; 
 int _krb5_num_checksums ; 

struct _krb5_checksum_type *
_krb5_find_checksum(krb5_cksumtype type)
{
    int i;
    for(i = 0; i < _krb5_num_checksums; i++)
	if(_krb5_checksum_types[i]->type == type)
	    return _krb5_checksum_types[i];
    return NULL;
}