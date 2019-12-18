#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_7__ {TYPE_1__ saltvalue; int /*<<< orphan*/  salttype; } ;
typedef  TYPE_2__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ETYPE_DES_CBC_CRC ; 
 scalar_t__ ETYPE_DES_CBC_MD4 ; 
 scalar_t__ ETYPE_DES_CBC_MD5 ; 
 int /*<<< orphan*/  KRB5_AFS3_SALT ; 
 int /*<<< orphan*/  KRB5_PW_SALT ; 
 scalar_t__ UI_UTIL_read_pw_string (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ afs ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/ * cell ; 
 void* estrdup (char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ help ; 
 int /*<<< orphan*/  keytype_str ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_salt (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  krb5_get_pw_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_parse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_program_setup (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_string_to_enctype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  num_args ; 
 char* password ; 
 int /*<<< orphan*/ * principal ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tokey (int /*<<< orphan*/ ,scalar_t__,char*,TYPE_2__,char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ version ; 
 scalar_t__ version4 ; 
 int version5 ; 

int
main(int argc, char **argv)
{
    krb5_context context;
    krb5_principal princ;
    krb5_salt salt;
    int optidx;
    char buf[1024];
    krb5_enctype etype;
    krb5_error_code ret;

    optidx = krb5_program_setup(&context, argc, argv, args, num_args, NULL);

    if(help)
	usage(0);

    if(version){
	print_version (NULL);
	return 0;
    }

    argc -= optidx;
    argv += optidx;

    if (argc > 1)
	usage(1);

    if(!version5 && !version4 && !afs)
	version5 = 1;

    ret = krb5_string_to_enctype(context, keytype_str, &etype);
    if(ret)
	krb5_err(context, 1, ret, "krb5_string_to_enctype");

    if((etype != ETYPE_DES_CBC_CRC &&
	etype != ETYPE_DES_CBC_MD4 &&
	etype != ETYPE_DES_CBC_MD5) &&
       (afs || version4)) {
	if(!version5) {
	    etype = ETYPE_DES_CBC_CRC;
	} else {
	    krb5_errx(context, 1,
		      "DES is the only valid keytype for AFS and Kerberos 4");
	}
    }

    if(version5 && principal == NULL){
	printf("Kerberos v5 principal: ");
	if(fgets(buf, sizeof(buf), stdin) == NULL)
	    return 1;
	buf[strcspn(buf, "\r\n")] = '\0';
	principal = estrdup(buf);
    }
    if(afs && cell == NULL){
	printf("AFS cell: ");
	if(fgets(buf, sizeof(buf), stdin) == NULL)
	    return 1;
	buf[strcspn(buf, "\r\n")] = '\0';
	cell = estrdup(buf);
    }
    if(argv[0])
	password = argv[0];
    if(password == NULL){
	if(UI_UTIL_read_pw_string(buf, sizeof(buf), "Password: ", 0))
	    return 1;
	password = buf;
    }

    if(version5){
	krb5_parse_name(context, principal, &princ);
	krb5_get_pw_salt(context, princ, &salt);
	tokey(context, etype, password, salt, "Kerberos 5 (%s)");
	krb5_free_salt(context, salt);
    }
    if(version4){
	salt.salttype = KRB5_PW_SALT;
	salt.saltvalue.length = 0;
	salt.saltvalue.data = NULL;
	tokey(context, ETYPE_DES_CBC_MD5, password, salt, "Kerberos 4");
    }
    if(afs){
	salt.salttype = KRB5_AFS3_SALT;
	salt.saltvalue.length = strlen(cell);
	salt.saltvalue.data = cell;
	tokey(context, ETYPE_DES_CBC_MD5, password, salt, "AFS");
    }
    return 0;
}