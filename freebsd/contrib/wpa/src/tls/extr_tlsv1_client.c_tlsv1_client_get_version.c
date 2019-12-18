#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tls_version; } ;
struct tlsv1_client {TYPE_1__ rl; } ;

/* Variables and functions */
#define  TLS_VERSION_1 130 
#define  TLS_VERSION_1_1 129 
#define  TLS_VERSION_1_2 128 
 int /*<<< orphan*/  os_strlcpy (char*,char*,size_t) ; 

int tlsv1_client_get_version(struct tlsv1_client *conn, char *buf,
			     size_t buflen)
{
	if (!conn)
		return -1;
	switch (conn->rl.tls_version) {
	case TLS_VERSION_1:
		os_strlcpy(buf, "TLSv1", buflen);
		break;
	case TLS_VERSION_1_1:
		os_strlcpy(buf, "TLSv1.1", buflen);
		break;
	case TLS_VERSION_1_2:
		os_strlcpy(buf, "TLSv1.2", buflen);
		break;
	default:
		return -1;
	}

	return 0;
}