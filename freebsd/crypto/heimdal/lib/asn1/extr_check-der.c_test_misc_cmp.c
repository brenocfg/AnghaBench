#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_13__ {int member_0; int /*<<< orphan*/ * data; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ heim_universal_string ;
struct TYPE_14__ {int member_0; char* member_1; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_15__ {int member_0; int* data; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_3__ heim_bmp_string ;
struct TYPE_16__ {int member_0; char* member_1; } ;
typedef  TYPE_4__ heim_bit_string ;

/* Variables and functions */
 int der_heim_bit_string_cmp (TYPE_4__ const*,TYPE_4__ const*) ; 
 int der_heim_bmp_string_cmp (TYPE_3__*,TYPE_3__*) ; 
 int der_heim_octet_string_cmp (TYPE_2__ const*,TYPE_2__ const*) ; 
 int der_heim_universal_string_cmp (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
test_misc_cmp(void)
{
    int ret;

    /* diffrent lengths are diffrent */
    {
	const heim_octet_string os1 = { 1, "a" } , os2 = { 0, NULL };
	ret = der_heim_octet_string_cmp(&os1, &os2);
	if (ret == 0)
	    return 1;
    }
    /* diffrent data are diffrent */
    {
	const heim_octet_string os1 = { 1, "a" } , os2 = { 1, "b" };
	ret = der_heim_octet_string_cmp(&os1, &os2);
	if (ret == 0)
	    return 1;
    }
    /* diffrent lengths are diffrent */
    {
	const heim_bit_string bs1 = { 8, "a" } , bs2 = { 7, "a" };
	ret = der_heim_bit_string_cmp(&bs1, &bs2);
	if (ret == 0)
	    return 1;
    }
    /* diffrent data are diffrent */
    {
	const heim_bit_string bs1 = { 7, "\x0f" } , bs2 = { 7, "\x02" };
	ret = der_heim_bit_string_cmp(&bs1, &bs2);
	if (ret == 0)
	    return 1;
    }
    /* diffrent lengths are diffrent */
    {
	uint16_t data = 1;
	heim_bmp_string bs1 = { 1, NULL } , bs2 = { 0, NULL };
	bs1.data = &data;
	ret = der_heim_bmp_string_cmp(&bs1, &bs2);
	if (ret == 0)
	    return 1;
    }
    /* diffrent lengths are diffrent */
    {
	uint32_t data;
	heim_universal_string us1 = { 1, NULL } , us2 = { 0, NULL };
	us1.data = &data;
	ret = der_heim_universal_string_cmp(&us1, &us2);
	if (ret == 0)
	    return 1;
    }
    /* same */
    {
	uint32_t data = (uint32_t)'a';
	heim_universal_string us1 = { 1, NULL } , us2 = { 1, NULL };
	us1.data = &data;
	us2.data = &data;
	ret = der_heim_universal_string_cmp(&us1, &us2);
	if (ret != 0)
	    return 1;
    }

    return 0;
}