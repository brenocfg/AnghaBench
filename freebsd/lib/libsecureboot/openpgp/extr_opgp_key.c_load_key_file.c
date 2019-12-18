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
typedef  int /*<<< orphan*/  OpenPGP_key ;

/* Variables and functions */
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/ * load_key_buf (unsigned char*,size_t) ; 
 int /*<<< orphan*/  openpgp_trust_add (int /*<<< orphan*/ *) ; 
 unsigned char* read_file (char const*,size_t*) ; 

OpenPGP_key *
load_key_file(const char *kfile)
{
	unsigned char *data = NULL;
	size_t n;
	OpenPGP_key *key;

	data = read_file(kfile, &n);
	key = load_key_buf(data, n);
	free(data);
	openpgp_trust_add(key);
	return (key);
}