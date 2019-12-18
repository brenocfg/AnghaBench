#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  password ;
struct TYPE_3__ {char const* prompt_info; char const* password; } ;
typedef  TYPE_1__ PW_CB_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OPENSSL_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* SRP_create_verifier (char const*,char*,char**,char**,char const*,char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 int password_callback (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static char *srp_verify_user(const char *user, const char *srp_verifier,
                             char *srp_usersalt, const char *g, const char *N,
                             const char *passin, int verbose)
{
    char password[1025];
    PW_CB_DATA cb_tmp;
    char *verifier = NULL;
    char *gNid = NULL;
    int len;

    cb_tmp.prompt_info = user;
    cb_tmp.password = passin;

    len = password_callback(password, sizeof(password)-1, 0, &cb_tmp);
    if (len > 0) {
        password[len] = 0;
        if (verbose)
            BIO_printf(bio_err,
                       "Validating\n   user=\"%s\"\n srp_verifier=\"%s\"\n srp_usersalt=\"%s\"\n g=\"%s\"\n N=\"%s\"\n",
                       user, srp_verifier, srp_usersalt, g, N);
        if (verbose > 1)
            BIO_printf(bio_err, "Pass %s\n", password);

        OPENSSL_assert(srp_usersalt != NULL);
        if ((gNid = SRP_create_verifier(user, password, &srp_usersalt,
                                        &verifier, N, g)) == NULL) {
            BIO_printf(bio_err, "Internal error validating SRP verifier\n");
        } else {
            if (strcmp(verifier, srp_verifier))
                gNid = NULL;
            OPENSSL_free(verifier);
        }
        OPENSSL_cleanse(password, len);
    }
    return gNid;
}