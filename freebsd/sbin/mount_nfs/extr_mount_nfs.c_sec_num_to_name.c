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

/* Variables and functions */
#define  AUTH_SYS 131 
#define  RPCSEC_GSS_KRB5 130 
#define  RPCSEC_GSS_KRB5I 129 
#define  RPCSEC_GSS_KRB5P 128 

__attribute__((used)) static const char *
sec_num_to_name(int flavor)
{
	switch (flavor) {
	case RPCSEC_GSS_KRB5:
		return ("krb5");
	case RPCSEC_GSS_KRB5I:
		return ("krb5i");
	case RPCSEC_GSS_KRB5P:
		return ("krb5p");
	case AUTH_SYS:
		return ("sys");
	}
	return (NULL);
}