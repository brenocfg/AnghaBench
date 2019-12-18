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
typedef  enum x509_name_attr_type { ____Placeholder_x509_name_attr_type } x509_name_attr_type ;

/* Variables and functions */
#define  X509_NAME_ATTR_C 135 
#define  X509_NAME_ATTR_CN 134 
#define  X509_NAME_ATTR_DC 133 
#define  X509_NAME_ATTR_L 132 
#define  X509_NAME_ATTR_NOT_USED 131 
#define  X509_NAME_ATTR_O 130 
#define  X509_NAME_ATTR_OU 129 
#define  X509_NAME_ATTR_ST 128 

__attribute__((used)) static char * x509_name_attr_str(enum x509_name_attr_type type)
{
	switch (type) {
	case X509_NAME_ATTR_NOT_USED:
		return "[N/A]";
	case X509_NAME_ATTR_DC:
		return "DC";
	case X509_NAME_ATTR_CN:
		return "CN";
	case X509_NAME_ATTR_C:
		return "C";
	case X509_NAME_ATTR_L:
		return "L";
	case X509_NAME_ATTR_ST:
		return "ST";
	case X509_NAME_ATTR_O:
		return "O";
	case X509_NAME_ATTR_OU:
		return "OU";
	}
	return "?";
}