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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
	    "usage: ssh-keygen [-q] [-b bits] [-t dsa | ecdsa | ed25519 | rsa]\n"
	    "                  [-N new_passphrase] [-C comment] [-f output_keyfile]\n"
	    "       ssh-keygen -p [-P old_passphrase] [-N new_passphrase] [-f keyfile]\n"
	    "       ssh-keygen -i [-m key_format] [-f input_keyfile]\n"
	    "       ssh-keygen -e [-m key_format] [-f input_keyfile]\n"
	    "       ssh-keygen -y [-f input_keyfile]\n"
	    "       ssh-keygen -c [-P passphrase] [-C comment] [-f keyfile]\n"
	    "       ssh-keygen -l [-v] [-E fingerprint_hash] [-f input_keyfile]\n"
	    "       ssh-keygen -B [-f input_keyfile]\n");
#ifdef ENABLE_PKCS11
	fprintf(stderr,
	    "       ssh-keygen -D pkcs11\n");
#endif
	fprintf(stderr,
	    "       ssh-keygen -F hostname [-f known_hosts_file] [-l]\n"
	    "       ssh-keygen -H [-f known_hosts_file]\n"
	    "       ssh-keygen -R hostname [-f known_hosts_file]\n"
	    "       ssh-keygen -r hostname [-f input_keyfile] [-g]\n"
#ifdef WITH_OPENSSL
	    "       ssh-keygen -G output_file [-v] [-b bits] [-M memory] [-S start_point]\n"
	    "       ssh-keygen -T output_file -f input_file [-v] [-a rounds] [-J num_lines]\n"
	    "                  [-j start_line] [-K checkpt] [-W generator]\n"
#endif
	    "       ssh-keygen -s ca_key -I certificate_identity [-h] [-U]\n"
	    "                  [-D pkcs11_provider] [-n principals] [-O option]\n"
	    "                  [-V validity_interval] [-z serial_number] file ...\n"
	    "       ssh-keygen -L [-f input_keyfile]\n"
	    "       ssh-keygen -A\n"
	    "       ssh-keygen -k -f krl_file [-u] [-s ca_public] [-z version_number]\n"
	    "                  file ...\n"
	    "       ssh-keygen -Q -f krl_file file ...\n");
	exit(1);
}