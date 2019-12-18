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
struct x509_name {int dummy; } ;
struct x509_certificate {int /*<<< orphan*/  subject; struct x509_certificate* next; } ;

/* Variables and functions */
 scalar_t__ x509_name_compare (int /*<<< orphan*/ *,struct x509_name*) ; 

struct x509_certificate *
x509_certificate_get_subject(struct x509_certificate *chain,
			     struct x509_name *name)
{
	struct x509_certificate *cert;

	for (cert = chain; cert; cert = cert->next) {
		if (x509_name_compare(&cert->subject, name) == 0)
			return cert;
	}
	return NULL;
}