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
 int /*<<< orphan*/  GNUTLS_VERSION ; 
 int /*<<< orphan*/  gnutls_check_version (int /*<<< orphan*/ *) ; 
 int os_snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_get_library_version(char *buf, size_t buf_len)
{
	return os_snprintf(buf, buf_len, "GnuTLS build=%s run=%s",
			   GNUTLS_VERSION, gnutls_check_version(NULL));
}