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
struct status_map_st {int member_0; char* member_1; } ;
struct TYPE_3__ {int /*<<< orphan*/ * failure_info; int /*<<< orphan*/  text; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ TS_STATUS_INFO ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long ASN1_INTEGER_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_STRING_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ OSSL_NELEM (char const**) ; 
#define  TS_INFO_ADD_INFO_NOT_AVAILABLE 135 
#define  TS_INFO_BAD_ALG 134 
#define  TS_INFO_BAD_DATA_FORMAT 133 
#define  TS_INFO_BAD_REQUEST 132 
#define  TS_INFO_SYSTEM_FAILURE 131 
#define  TS_INFO_TIME_NOT_AVAILABLE 130 
#define  TS_INFO_UNACCEPTED_EXTENSION 129 
#define  TS_INFO_UNACCEPTED_POLICY 128 
 int sk_ASN1_UTF8STRING_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ASN1_UTF8STRING_value (int /*<<< orphan*/ ,int) ; 
 int ts_status_map_print (int /*<<< orphan*/ *,struct status_map_st const*,int /*<<< orphan*/ *) ; 

int TS_STATUS_INFO_print_bio(BIO *bio, TS_STATUS_INFO *a)
{
    static const char *status_map[] = {
        "Granted.",
        "Granted with modifications.",
        "Rejected.",
        "Waiting.",
        "Revocation warning.",
        "Revoked."
    };
    static const struct status_map_st failure_map[] = {
        {TS_INFO_BAD_ALG,
         "unrecognized or unsupported algorithm identifier"},
        {TS_INFO_BAD_REQUEST,
         "transaction not permitted or supported"},
        {TS_INFO_BAD_DATA_FORMAT,
         "the data submitted has the wrong format"},
        {TS_INFO_TIME_NOT_AVAILABLE,
         "the TSA's time source is not available"},
        {TS_INFO_UNACCEPTED_POLICY,
         "the requested TSA policy is not supported by the TSA"},
        {TS_INFO_UNACCEPTED_EXTENSION,
         "the requested extension is not supported by the TSA"},
        {TS_INFO_ADD_INFO_NOT_AVAILABLE,
         "the additional information requested could not be understood "
         "or is not available"},
        {TS_INFO_SYSTEM_FAILURE,
         "the request cannot be handled due to system failure"},
        {-1, NULL}
    };
    long status;
    int i, lines = 0;

    BIO_printf(bio, "Status: ");
    status = ASN1_INTEGER_get(a->status);
    if (0 <= status && status < (long)OSSL_NELEM(status_map))
        BIO_printf(bio, "%s\n", status_map[status]);
    else
        BIO_printf(bio, "out of bounds\n");

    BIO_printf(bio, "Status description: ");
    for (i = 0; i < sk_ASN1_UTF8STRING_num(a->text); ++i) {
        if (i > 0)
            BIO_puts(bio, "\t");
        ASN1_STRING_print_ex(bio, sk_ASN1_UTF8STRING_value(a->text, i), 0);
        BIO_puts(bio, "\n");
    }
    if (i == 0)
        BIO_printf(bio, "unspecified\n");

    BIO_printf(bio, "Failure info: ");
    if (a->failure_info != NULL)
        lines = ts_status_map_print(bio, failure_map, a->failure_info);
    if (lines == 0)
        BIO_printf(bio, "unspecified");
    BIO_printf(bio, "\n");

    return 1;
}