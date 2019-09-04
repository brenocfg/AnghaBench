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
struct TYPE_3__ {void* path; void* username; void* protocol; int /*<<< orphan*/  password; } ;

/* Variables and functions */
 TYPE_1__ cert_auth ; 
 int /*<<< orphan*/  credential_fill (TYPE_1__*) ; 
 char* ssl_cert ; 
 int ssl_cert_password_required ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static int has_cert_password(void)
{
	if (ssl_cert == NULL || ssl_cert_password_required != 1)
		return 0;
	if (!cert_auth.password) {
		cert_auth.protocol = xstrdup("cert");
		cert_auth.username = xstrdup("");
		cert_auth.path = xstrdup(ssl_cert);
		credential_fill(&cert_auth);
	}
	return 1;
}