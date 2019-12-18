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
struct stash_options {char* key_file_string; int master_key_fd_integer; scalar_t__ random_password_flag; scalar_t__ convert_file_flag; int /*<<< orphan*/  enctype_string; } ;
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
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  KRB5_PW_SALT ; 
 scalar_t__ UI_UTIL_read_pw_string (char*,int,char*,int) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  context ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hdb_add_master_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* hdb_db_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdb_free_master_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hdb_read_master_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_write_master_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_string_to_enctype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_string_to_key_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ link (char*,char*) ; 
 int /*<<< orphan*/  local_flag ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  random_password (char*,int) ; 
 size_t read (int,char*,int) ; 
 scalar_t__ rename (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ unlink (char*) ; 

int
stash(struct stash_options *opt, int argc, char **argv)
{
    char buf[1024];
    krb5_error_code ret;
    krb5_enctype enctype;
    hdb_master_key mkey;

    if(!local_flag) {
	krb5_warnx(context, "stash is only available in local (-l) mode");
	return 0;
    }

    ret = krb5_string_to_enctype(context, opt->enctype_string, &enctype);
    if(ret) {
	krb5_warn(context, ret, "%s", opt->enctype_string);
	return 0;
    }

    if(opt->key_file_string == NULL) {
	asprintf(&opt->key_file_string, "%s/m-key", hdb_db_dir(context));
	if (opt->key_file_string == NULL)
	    errx(1, "out of memory");
    }

    ret = hdb_read_master_key(context, opt->key_file_string, &mkey);
    if(ret && ret != ENOENT) {
	krb5_warn(context, ret, "reading master key from %s",
		  opt->key_file_string);
	return 0;
    }

    if (opt->convert_file_flag) {
	if (ret)
	    krb5_warn(context, ret, "reading master key from %s",
		      opt->key_file_string);
	return 0;
    } else {
	krb5_keyblock key;
	krb5_salt salt;
	salt.salttype = KRB5_PW_SALT;
	/* XXX better value? */
	salt.saltvalue.data = NULL;
	salt.saltvalue.length = 0;
	if(opt->master_key_fd_integer != -1) {
	    ssize_t n;
	    n = read(opt->master_key_fd_integer, buf, sizeof(buf));
	    if(n == 0)
		krb5_warnx(context, "end of file reading passphrase");
	    else if(n < 0) {
		krb5_warn(context, errno, "reading passphrase");
		n = 0;
	    }
	    buf[n] = '\0';
	    buf[strcspn(buf, "\r\n")] = '\0';
	} else if (opt->random_password_flag) {
	    random_password (buf, sizeof(buf));
	    printf("Using random master stash password: %s\n", buf);
	} else {
	    if(UI_UTIL_read_pw_string(buf, sizeof(buf), "Master key: ", 1)) {
		hdb_free_master_key(context, mkey);
		return 0;
	    }
	}
	ret = krb5_string_to_key_salt(context, enctype, buf, salt, &key);
	ret = hdb_add_master_key(context, &key, &mkey);
	krb5_free_keyblock_contents(context, &key);
    }

    {
	char *new, *old;
	asprintf(&old, "%s.old", opt->key_file_string);
	asprintf(&new, "%s.new", opt->key_file_string);
	if(old == NULL || new == NULL) {
	    ret = ENOMEM;
	    goto out;
	}

	if(unlink(new) < 0 && errno != ENOENT) {
	    ret = errno;
	    goto out;
	}
	krb5_warnx(context, "writing key to \"%s\"", opt->key_file_string);
	ret = hdb_write_master_key(context, new, mkey);
	if(ret)
	    unlink(new);
	else {
	    unlink(old);
#ifndef NO_POSIX_LINKS
	    if(link(opt->key_file_string, old) < 0 && errno != ENOENT) {
		ret = errno;
		unlink(new);
	    } else {
#endif
		if(rename(new, opt->key_file_string) < 0) {
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
    return 0;
}