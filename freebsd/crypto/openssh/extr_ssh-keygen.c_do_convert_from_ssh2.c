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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int dummy; } ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  encoded ;
typedef  int /*<<< orphan*/  blob ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* SSH_COM_PRIVATE_BEGIN ; 
 int /*<<< orphan*/  __progname ; 
 struct sshkey* do_convert_private_ssh2_from_blob (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int get_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  identity_file ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int sshkey_from_blob (int /*<<< orphan*/ *,int,struct sshkey**) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int uudecode (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
do_convert_from_ssh2(struct passwd *pw, struct sshkey **k, int *private)
{
	int r, blen, escaped = 0;
	u_int len;
	char line[1024];
	u_char blob[8096];
	char encoded[8096];
	FILE *fp;

	if ((fp = fopen(identity_file, "r")) == NULL)
		fatal("%s: %s: %s", __progname, identity_file, strerror(errno));
	encoded[0] = '\0';
	while ((blen = get_line(fp, line, sizeof(line))) != -1) {
		if (blen > 0 && line[blen - 1] == '\\')
			escaped++;
		if (strncmp(line, "----", 4) == 0 ||
		    strstr(line, ": ") != NULL) {
			if (strstr(line, SSH_COM_PRIVATE_BEGIN) != NULL)
				*private = 1;
			if (strstr(line, " END ") != NULL) {
				break;
			}
			/* fprintf(stderr, "ignore: %s", line); */
			continue;
		}
		if (escaped) {
			escaped--;
			/* fprintf(stderr, "escaped: %s", line); */
			continue;
		}
		strlcat(encoded, line, sizeof(encoded));
	}
	len = strlen(encoded);
	if (((len % 4) == 3) &&
	    (encoded[len-1] == '=') &&
	    (encoded[len-2] == '=') &&
	    (encoded[len-3] == '='))
		encoded[len-3] = '\0';
	blen = uudecode(encoded, blob, sizeof(blob));
	if (blen < 0)
		fatal("uudecode failed.");
	if (*private)
		*k = do_convert_private_ssh2_from_blob(blob, blen);
	else if ((r = sshkey_from_blob(blob, blen, k)) != 0)
		fatal("decode blob failed: %s", ssh_err(r));
	fclose(fp);
}