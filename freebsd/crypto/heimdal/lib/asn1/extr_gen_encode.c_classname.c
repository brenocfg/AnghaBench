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
typedef  size_t Der_class ;

/* Variables and functions */
 size_t ASN1_C_PRIVATE ; 
 size_t ASN1_C_UNIV ; 

const char *
classname(Der_class class)
{
    const char *cn[] = { "ASN1_C_UNIV", "ASN1_C_APPL",
			 "ASN1_C_CONTEXT", "ASN1_C_PRIV" };
    if(class < ASN1_C_UNIV || class > ASN1_C_PRIVATE)
	return "???";
    return cn[class];
}