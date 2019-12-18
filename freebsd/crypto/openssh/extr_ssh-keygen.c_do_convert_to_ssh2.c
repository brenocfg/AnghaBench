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
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int dummy; } ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  comment ;

/* Variables and functions */
 char* SSH_COM_PUBLIC_BEGIN ; 
 char* SSH_COM_PUBLIC_END ; 
 int /*<<< orphan*/  dump_base64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* hostname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_size (struct sshkey*) ; 
 int sshkey_to_blob (struct sshkey*,int /*<<< orphan*/ **,size_t*) ; 
 char* sshkey_type (struct sshkey*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
do_convert_to_ssh2(struct passwd *pw, struct sshkey *k)
{
	size_t len;
	u_char *blob;
	char comment[61];
	int r;

	if ((r = sshkey_to_blob(k, &blob, &len)) != 0)
		fatal("key_to_blob failed: %s", ssh_err(r));
	/* Comment + surrounds must fit into 72 chars (RFC 4716 sec 3.3) */
	snprintf(comment, sizeof(comment),
	    "%u-bit %s, converted by %s@%s from OpenSSH",
	    sshkey_size(k), sshkey_type(k),
	    pw->pw_name, hostname);

	fprintf(stdout, "%s\n", SSH_COM_PUBLIC_BEGIN);
	fprintf(stdout, "Comment: \"%s\"\n", comment);
	dump_base64(stdout, blob, len);
	fprintf(stdout, "%s\n", SSH_COM_PUBLIC_END);
	sshkey_free(k);
	free(blob);
	exit(0);
}