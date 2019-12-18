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
struct TYPE_3__ {scalar_t__ type; int length; unsigned char* data; } ;
typedef  TYPE_1__ ASN1_UNIVERSALSTRING ;

/* Variables and functions */
 scalar_t__ ASN1_PRINTABLE_type (unsigned char*,int) ; 
 scalar_t__ V_ASN1_UNIVERSALSTRING ; 

int ASN1_UNIVERSALSTRING_to_string(ASN1_UNIVERSALSTRING *s)
{
    int i;
    unsigned char *p;

    if (s->type != V_ASN1_UNIVERSALSTRING)
        return 0;
    if ((s->length % 4) != 0)
        return 0;
    p = s->data;
    for (i = 0; i < s->length; i += 4) {
        if ((p[0] != '\0') || (p[1] != '\0') || (p[2] != '\0'))
            break;
        else
            p += 4;
    }
    if (i < s->length)
        return 0;
    p = s->data;
    for (i = 3; i < s->length; i += 4) {
        *(p++) = s->data[i];
    }
    *(p) = '\0';
    s->length /= 4;
    s->type = ASN1_PRINTABLE_type(s->data, s->length);
    return 1;
}