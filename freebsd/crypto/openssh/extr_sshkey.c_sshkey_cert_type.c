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
struct sshkey {TYPE_1__* cert; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  SSH2_CERT_TYPE_HOST 129 
#define  SSH2_CERT_TYPE_USER 128 

const char *
sshkey_cert_type(const struct sshkey *k)
{
	switch (k->cert->type) {
	case SSH2_CERT_TYPE_USER:
		return "user";
	case SSH2_CERT_TYPE_HOST:
		return "host";
	default:
		return "unknown";
	}
}