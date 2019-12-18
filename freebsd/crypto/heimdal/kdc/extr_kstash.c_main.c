#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {TYPE_1__ saltvalue; int /*<<< orphan*/  salttype; } ;
typedef  TYPE_2__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  hdb_master_key ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  KRB5_PW_SALT ; 
 scalar_t__ UI_UTIL_read_pw_string (char*,int,char*,int) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  context ; 
 scalar_t__ convert_flag ; 
 int /*<<< orphan*/  enctype_str ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hdb_add_master_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* hdb_db_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_free_master_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hdb_read_master_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_write_master_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ help_flag ; 
 char* keyfile ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_generate_random_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_program_setup (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_std_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_string_to_enctype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_string_to_key_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ link (char*,char*) ; 
 int master_key_fd ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 scalar_t__ random_key_flag ; 
 size_t read (int,char*,int) ; 
 scalar_t__ rename (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ unlink (char*) ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
    char buf[1024];
    krb5_error_code ret;

    krb5_enctype enctype;

    hdb_master_key mkey;

    krb5_program_setup(&context, argc, argv, args, num_args, NULL);

    if(help_flag)
	krb5_std_usage(0, args, num_args);
    if(version_flag){
	print_version(NULL);
	exit(0);
    }

    if (master_key_fd != -1 && random_key_flag)
	krb5_errx(context, 1, "random-key and master-key-fd "
		  "is mutual exclusive");

    if (keyfile == NULL)
	asprintf(&keyfile, "%s/m-key", hdb_db_dir(context));

    ret = krb5_string_to_enctype(context, enctype_str, &enctype);
    if(ret)
	krb5_err(context, 1, ret, "krb5_string_to_enctype");

    ret = hdb_read_master_key(context, keyfile, &mkey);
    if(ret && ret != ENOENT)
	krb5_err(context, 1, ret, "reading master key from %s", keyfile);

    if (convert_flag) {
	if (ret)
	    krb5_err(context, 1, ret, "reading master key from %s", keyfile);
    } else {
	krb5_keyblock key;
	krb5_salt salt;
	salt.salttype = KRB5_PW_SALT;
	/* XXX better value? */
	salt.saltvalue.data = NULL;
	salt.saltvalue.length = 0;
	if (random_key_flag) {
	    ret = krb5_generate_random_keyblock(context, enctype, &key);
	    if (ret)
		krb5_err(context, 1, ret, "krb5_generate_random_keyblock");

	} else {
	    if(master_key_fd != -1) {
		ssize_t n;
		n = read(master_key_fd, buf, sizeof(buf));
		if(n <= 0)
		    krb5_err(context, 1, errno, "failed to read passphrase");
		buf[n] = '\0';
		buf[strcspn(buf, "\r\n")] = '\0';

	    } else {
		if(UI_UTIL_read_pw_string(buf, sizeof(buf), "Master key: ", 1))
		    exit(1);
	    }
	    krb5_string_to_key_salt(context, enctype, buf, salt, &key);
	}
	ret = hdb_add_master_key(context, &key, &mkey);

	krb5_free_keyblock_contents(context, &key);

    }

    {
	char *new, *old;
	asprintf(&old, "%s.old", keyfile);
	asprintf(&new, "%s.new", keyfile);
	if(unlink(new) < 0 && errno != ENOENT) {
	    ret = errno;
	    goto out;
	}
	krb5_warnx(context, "writing key to `%s'", keyfile);
	ret = hdb_write_master_key(context, new, mkey);
	if(ret)
	    unlink(new);
	else {
#ifndef NO_POSIX_LINKS
	    unlink(old);
	    if(link(keyfile, old) < 0 && errno != ENOENT) {
		ret = errno;
		unlink(new);
	    } else {
#endif
		if(rename(new, keyfile) < 0) {
		    ret = errno;
		}
#ifndef NO_POSIX_LINKS
	    }
#endif
	}
    out:
	free(old);
	free(new);
	if(ret)
	    krb5_warn(context, errno, "writing master key file");
    }

    hdb_free_master_key(context, mkey);

    exit(ret != 0);
}