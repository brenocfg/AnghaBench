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
struct sshkey {int type; int ecdsa_nid; } ;
struct ssh {int dummy; } ;
struct TYPE_4__ {size_t num_host_key_files; } ;
struct TYPE_3__ {struct sshkey** host_keys; struct sshkey** host_pubkeys; struct sshkey** host_certificates; } ;

/* Variables and functions */
#define  KEY_DSA_CERT 132 
 int KEY_ECDSA ; 
#define  KEY_ECDSA_CERT 131 
#define  KEY_ED25519_CERT 130 
#define  KEY_RSA_CERT 129 
#define  KEY_XMSS_CERT 128 
 TYPE_2__ options ; 
 TYPE_1__ sensitive_data ; 

__attribute__((used)) static struct sshkey *
get_hostkey_by_type(int type, int nid, int need_private, struct ssh *ssh)
{
	u_int i;
	struct sshkey *key;

	for (i = 0; i < options.num_host_key_files; i++) {
		switch (type) {
		case KEY_RSA_CERT:
		case KEY_DSA_CERT:
		case KEY_ECDSA_CERT:
		case KEY_ED25519_CERT:
		case KEY_XMSS_CERT:
			key = sensitive_data.host_certificates[i];
			break;
		default:
			key = sensitive_data.host_keys[i];
			if (key == NULL && !need_private)
				key = sensitive_data.host_pubkeys[i];
			break;
		}
		if (key != NULL && key->type == type &&
		    (key->type != KEY_ECDSA || key->ecdsa_nid == nid))
			return need_private ?
			    sensitive_data.host_keys[i] : key;
	}
	return NULL;
}