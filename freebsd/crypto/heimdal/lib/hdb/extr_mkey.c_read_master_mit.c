#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_4__ {int /*<<< orphan*/  keyvalue; int /*<<< orphan*/  keytype; } ;
typedef  TYPE_1__ krb5_keyblock ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  hdb_master_key ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int hdb_process_master_key (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_enctype_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int krb5_ret_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_ret_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  krb5_storage_set_flags (int /*<<< orphan*/ *,int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static krb5_error_code
read_master_mit(krb5_context context, const char *filename,
		int byteorder, hdb_master_key *mkey)
{
    int fd;
    krb5_error_code ret;
    krb5_storage *sp;
    int16_t enctype;
    krb5_keyblock key;

    fd = open(filename, O_RDONLY | O_BINARY);
    if(fd < 0) {
	int save_errno = errno;
	krb5_set_error_message(context, save_errno, "failed to open %s: %s",
			       filename, strerror(save_errno));
	return save_errno;
    }
    sp = krb5_storage_from_fd(fd);
    if(sp == NULL) {
	close(fd);
	return errno;
    }
    krb5_storage_set_flags(sp, byteorder);
    /* could possibly use ret_keyblock here, but do it with more
       checks for now */
    {
	ret = krb5_ret_int16(sp, &enctype);
	if (ret)
	    goto out;
	ret = krb5_enctype_valid(context, enctype);
	if (ret)
	   goto out;
	key.keytype = enctype;
	ret = krb5_ret_data(sp, &key.keyvalue);
	if(ret)
	    goto out;
    }
    ret = hdb_process_master_key(context, 1, &key, 0, mkey);
    krb5_free_keyblock_contents(context, &key);
  out:
    krb5_storage_free(sp);
    close(fd);
    return ret;
}