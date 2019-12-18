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
typedef  scalar_t__ u_int ;
struct sshkey {int dummy; } ;
struct ssh {int dummy; } ;
struct TYPE_4__ {scalar_t__ num_host_key_files; } ;
struct TYPE_3__ {struct sshkey** host_pubkeys; } ;

/* Variables and functions */
 TYPE_2__ options ; 
 TYPE_1__ sensitive_data ; 

struct sshkey *
get_hostkey_public_by_index(int ind, struct ssh *ssh)
{
	if (ind < 0 || (u_int)ind >= options.num_host_key_files)
		return (NULL);
	return (sensitive_data.host_pubkeys[ind]);
}