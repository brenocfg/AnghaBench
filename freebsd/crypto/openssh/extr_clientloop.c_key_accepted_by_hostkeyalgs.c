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
struct sshkey {scalar_t__ type; } ;
struct TYPE_2__ {char* hostkeyalgorithms; } ;

/* Variables and functions */
 char* KEX_DEFAULT_PK_ALG ; 
 scalar_t__ KEY_RSA ; 
 scalar_t__ KEY_UNSPEC ; 
 int match_pattern_list (char const*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ options ; 
 char* sshkey_ssh_name (struct sshkey const*) ; 

__attribute__((used)) static int
key_accepted_by_hostkeyalgs(const struct sshkey *key)
{
	const char *ktype = sshkey_ssh_name(key);
	const char *hostkeyalgs = options.hostkeyalgorithms != NULL ?
	    options.hostkeyalgorithms : KEX_DEFAULT_PK_ALG;

	if (key == NULL || key->type == KEY_UNSPEC)
		return 0;
	if (key->type == KEY_RSA &&
	    (match_pattern_list("rsa-sha2-256", hostkeyalgs, 0) == 1 ||
	    match_pattern_list("rsa-sha2-512", hostkeyalgs, 0) == 1))
		return 1;
	return match_pattern_list(ktype, hostkeyalgs, 0) == 1;
}