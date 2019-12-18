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
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_3__ {int length; char* data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  classes ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int krb5_config_get_int_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 size_t strcspn (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
char_class_passwd_quality (krb5_context context,
			   krb5_principal principal,
			   krb5_data *pwd,
			   const char *opaque,
			   char *message,
			   size_t length)
{
    const char *classes[] = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	"abcdefghijklmnopqrstuvwxyz",
	"1234567890",
	"!@#$%^&*()/?<>,.{[]}\\|'~`\" "
    };
    int counter = 0, req_classes;
    size_t i, len;
    char *pw;

    req_classes = krb5_config_get_int_default(context, NULL, 3,
					      "password_quality",
					      "min_classes",
					      NULL);

    len = pwd->length + 1;
    pw = malloc(len);
    if (pw == NULL) {
	strlcpy(message, "out of memory", length);
	return 1;
    }
    strlcpy(pw, pwd->data, len);
    len = strlen(pw);

    for (i = 0; i < sizeof(classes)/sizeof(classes[0]); i++) {
	if (strcspn(pw, classes[i]) < len)
	    counter++;
    }
    memset(pw, 0, pwd->length + 1);
    free(pw);
    if (counter < req_classes) {
	snprintf(message, length,
	    "Password doesn't meet complexity requirement.\n"
	    "Add more characters from the following classes:\n"
	    "1. English uppercase characters (A through Z)\n"
	    "2. English lowercase characters (a through z)\n"
	    "3. Base 10 digits (0 through 9)\n"
	    "4. Nonalphanumeric characters (e.g., !, $, #, %%)");
	return 1;
    }
    return 0;
}