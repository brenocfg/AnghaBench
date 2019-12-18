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
struct sshkey {int type; } ;
struct keytype {int type; char const* shortname; } ;

/* Variables and functions */
 struct keytype* keytypes ; 

const char *
sshkey_type(const struct sshkey *k)
{
	const struct keytype *kt;

	for (kt = keytypes; kt->type != -1; kt++) {
		if (kt->type == k->type)
			return kt->shortname;
	}
	return "unknown";
}