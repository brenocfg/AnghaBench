#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_name ;
struct TYPE_6__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_5__ {int /*<<< orphan*/  der_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_MALLOC_ENCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  Name ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 

int
hx509_name_binary(const hx509_name name, heim_octet_string *os)
{
    size_t size;
    int ret;

    ASN1_MALLOC_ENCODE(Name, os->data, os->length, &name->der_name, &size, ret);
    if (ret)
	return ret;
    if (os->length != size)
	_hx509_abort("internal ASN.1 encoder error");

    return 0;
}