#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct sshkey {int dummy; } ;
struct ssh {int dummy; } ;
struct TYPE_4__ {size_t num_host_key_files; } ;
struct TYPE_3__ {struct sshkey** host_pubkeys; struct sshkey** host_keys; struct sshkey** host_certificates; } ;

/* Variables and functions */
 TYPE_2__ options ; 
 TYPE_1__ sensitive_data ; 
 scalar_t__ sshkey_equal (struct sshkey*,struct sshkey*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey*) ; 

int
get_hostkey_index(struct sshkey *key, int compare, struct ssh *ssh)
{
	u_int i;

	for (i = 0; i < options.num_host_key_files; i++) {
		if (sshkey_is_cert(key)) {
			if (key == sensitive_data.host_certificates[i] ||
			    (compare && sensitive_data.host_certificates[i] &&
			    sshkey_equal(key,
			    sensitive_data.host_certificates[i])))
				return (i);
		} else {
			if (key == sensitive_data.host_keys[i] ||
			    (compare && sensitive_data.host_keys[i] &&
			    sshkey_equal(key, sensitive_data.host_keys[i])))
				return (i);
			if (key == sensitive_data.host_pubkeys[i] ||
			    (compare && sensitive_data.host_pubkeys[i] &&
			    sshkey_equal(key, sensitive_data.host_pubkeys[i])))
				return (i);
		}
	}
	return (-1);
}