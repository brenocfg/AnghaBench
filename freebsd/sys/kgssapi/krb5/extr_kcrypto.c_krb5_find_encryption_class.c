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
struct krb5_encryption_class {int ec_type; } ;

/* Variables and functions */
 struct krb5_encryption_class** krb5_encryption_classes ; 

struct krb5_encryption_class *
krb5_find_encryption_class(int etype)
{
	int i;

	for (i = 0; krb5_encryption_classes[i]; i++) {
		if (krb5_encryption_classes[i]->ec_type == etype)
			return (krb5_encryption_classes[i]);
	}
	return (NULL);
}