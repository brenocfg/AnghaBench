#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct strstr_pair_st   TYPE_1__ ;

/* Type definitions */
struct strstr_pair_st {char* prefix; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 size_t OSSL_NELEM (TYPE_1__*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opt_number_error(const char *v)
{
    size_t i = 0;
    struct strstr_pair_st {
        char *prefix;
        char *name;
    } b[] = {
        {"0x", "a hexadecimal"},
        {"0X", "a hexadecimal"},
        {"0", "an octal"}
    };

    for (i = 0; i < OSSL_NELEM(b); i++) {
        if (strncmp(v, b[i].prefix, strlen(b[i].prefix)) == 0) {
            BIO_printf(bio_err,
                       "%s: Can't parse \"%s\" as %s number\n",
                       prog, v, b[i].name);
            return;
        }
    }
    BIO_printf(bio_err, "%s: Can't parse \"%s\" as a number\n", prog, v);
    return;
}