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
typedef  int /*<<< orphan*/  newkey ;
typedef  int /*<<< orphan*/  OtpKey ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  generate_password (char**,int,char*,int,char*,int,char*,int) ; 
 int /*<<< orphan*/  krb5_generate_random_block (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otp_print_stddict (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strlwr (char*) ; 

void
random_password(char *pw, size_t len)
{
#ifdef OTP_STYLE
    {
	OtpKey newkey;

	krb5_generate_random_block(&newkey, sizeof(newkey));
	otp_print_stddict (newkey, pw, len);
	strlwr(pw);
    }
#else
    char *pass;
    generate_password(&pass, 3,
		      "abcdefghijklmnopqrstuvwxyz", 7,
		      "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 2,
		      "@$%&*()-+=:,/<>1234567890", 1);
    strlcpy(pw, pass, len);
    memset(pass, 0, strlen(pass));
    free(pass);
#endif
}