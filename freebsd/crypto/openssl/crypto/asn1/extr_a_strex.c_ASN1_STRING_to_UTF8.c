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
struct TYPE_4__ {int type; unsigned char* data; int length; scalar_t__ flags; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int ASN1_mbstring_copy (TYPE_1__**,unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_ASN1_UTF8STRING ; 
 int MBSTRING_FLAG ; 
 int* tag2nbyte ; 

int ASN1_STRING_to_UTF8(unsigned char **out, const ASN1_STRING *in)
{
    ASN1_STRING stmp, *str = &stmp;
    int mbflag, type, ret;
    if (!in)
        return -1;
    type = in->type;
    if ((type < 0) || (type > 30))
        return -1;
    mbflag = tag2nbyte[type];
    if (mbflag == -1)
        return -1;
    mbflag |= MBSTRING_FLAG;
    stmp.data = NULL;
    stmp.length = 0;
    stmp.flags = 0;
    ret =
        ASN1_mbstring_copy(&str, in->data, in->length, mbflag,
                           B_ASN1_UTF8STRING);
    if (ret < 0)
        return ret;
    *out = stmp.data;
    return stmp.length;
}