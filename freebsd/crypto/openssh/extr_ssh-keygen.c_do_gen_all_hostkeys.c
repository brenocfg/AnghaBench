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
struct stat {scalar_t__ st_size; } ;
struct sshkey {int dummy; } ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/ * _PATH_HOST_DSA_KEY_FILE ; 
 int /*<<< orphan*/ * _PATH_HOST_ECDSA_KEY_FILE ; 
 int /*<<< orphan*/ * _PATH_HOST_ED25519_KEY_FILE ; 
 int /*<<< orphan*/ * _PATH_HOST_RSA_KEY_FILE ; 
 int /*<<< orphan*/ * _PATH_HOST_XMSS_KEY_FILE ; 
 char* __progname ; 
 scalar_t__ bits ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hostname ; 
 int /*<<< orphan*/  identity_file ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  new_format_cipher ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  rounds ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* ssh_err (int) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_from_private (struct sshkey*,struct sshkey**) ; 
 int sshkey_generate (int,scalar_t__,struct sshkey**) ; 
 int sshkey_save_private (struct sshkey*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshkey_type_from_name (char*) ; 
 int sshkey_write (struct sshkey*,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  type_bits_valid (int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  use_new_format ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_gen_all_hostkeys(struct passwd *pw)
{
	struct {
		char *key_type;
		char *key_type_display;
		char *path;
	} key_types[] = {
#ifdef WITH_OPENSSL
		{ "rsa", "RSA" ,_PATH_HOST_RSA_KEY_FILE },
		{ "dsa", "DSA", _PATH_HOST_DSA_KEY_FILE },
#ifdef OPENSSL_HAS_ECC
		{ "ecdsa", "ECDSA",_PATH_HOST_ECDSA_KEY_FILE },
#endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */
		{ "ed25519", "ED25519",_PATH_HOST_ED25519_KEY_FILE },
#ifdef WITH_XMSS
		{ "xmss", "XMSS",_PATH_HOST_XMSS_KEY_FILE },
#endif /* WITH_XMSS */
		{ NULL, NULL, NULL }
	};

	int first = 0;
	struct stat st;
	struct sshkey *private, *public;
	char comment[1024], *prv_tmp, *pub_tmp, *prv_file, *pub_file;
	int i, type, fd, r;
	FILE *f;

	for (i = 0; key_types[i].key_type; i++) {
		public = private = NULL;
		prv_tmp = pub_tmp = prv_file = pub_file = NULL;

		xasprintf(&prv_file, "%s%s",
		    identity_file, key_types[i].path);

		/* Check whether private key exists and is not zero-length */
		if (stat(prv_file, &st) == 0) {
			if (st.st_size != 0)
				goto next;
		} else if (errno != ENOENT) {
			error("Could not stat %s: %s", key_types[i].path,
			    strerror(errno));
			goto failnext;
		}

		/*
		 * Private key doesn't exist or is invalid; proceed with
		 * key generation.
		 */
		xasprintf(&prv_tmp, "%s%s.XXXXXXXXXX",
		    identity_file, key_types[i].path);
		xasprintf(&pub_tmp, "%s%s.pub.XXXXXXXXXX",
		    identity_file, key_types[i].path);
		xasprintf(&pub_file, "%s%s.pub",
		    identity_file, key_types[i].path);

		if (first == 0) {
			first = 1;
			printf("%s: generating new host keys: ", __progname);
		}
		printf("%s ", key_types[i].key_type_display);
		fflush(stdout);
		type = sshkey_type_from_name(key_types[i].key_type);
		if ((fd = mkstemp(prv_tmp)) == -1) {
			error("Could not save your public key in %s: %s",
			    prv_tmp, strerror(errno));
			goto failnext;
		}
		close(fd); /* just using mkstemp() to generate/reserve a name */
		bits = 0;
		type_bits_valid(type, NULL, &bits);
		if ((r = sshkey_generate(type, bits, &private)) != 0) {
			error("sshkey_generate failed: %s", ssh_err(r));
			goto failnext;
		}
		if ((r = sshkey_from_private(private, &public)) != 0)
			fatal("sshkey_from_private failed: %s", ssh_err(r));
		snprintf(comment, sizeof comment, "%s@%s", pw->pw_name,
		    hostname);
		if ((r = sshkey_save_private(private, prv_tmp, "",
		    comment, use_new_format, new_format_cipher, rounds)) != 0) {
			error("Saving key \"%s\" failed: %s",
			    prv_tmp, ssh_err(r));
			goto failnext;
		}
		if ((fd = mkstemp(pub_tmp)) == -1) {
			error("Could not save your public key in %s: %s",
			    pub_tmp, strerror(errno));
			goto failnext;
		}
		(void)fchmod(fd, 0644);
		f = fdopen(fd, "w");
		if (f == NULL) {
			error("fdopen %s failed: %s", pub_tmp, strerror(errno));
			close(fd);
			goto failnext;
		}
		if ((r = sshkey_write(public, f)) != 0) {
			error("write key failed: %s", ssh_err(r));
			fclose(f);
			goto failnext;
		}
		fprintf(f, " %s\n", comment);
		if (ferror(f) != 0) {
			error("write key failed: %s", strerror(errno));
			fclose(f);
			goto failnext;
		}
		if (fclose(f) != 0) {
			error("key close failed: %s", strerror(errno));
			goto failnext;
		}

		/* Rename temporary files to their permanent locations. */
		if (rename(pub_tmp, pub_file) != 0) {
			error("Unable to move %s into position: %s",
			    pub_file, strerror(errno));
			goto failnext;
		}
		if (rename(prv_tmp, prv_file) != 0) {
			error("Unable to move %s into position: %s",
			    key_types[i].path, strerror(errno));
 failnext:
			first = 0;
			goto next;
		}
 next:
		sshkey_free(private);
		sshkey_free(public);
		free(prv_tmp);
		free(pub_tmp);
		free(prv_file);
		free(pub_file);
	}
	if (first != 0)
		printf("\n");
}