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
struct TYPE_3__ {int /*<<< orphan*/ * micros; int /*<<< orphan*/ * millis; int /*<<< orphan*/ * seconds; } ;
typedef  TYPE_1__ TS_ACCURACY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TS_ASN1_INTEGER_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ts_ACCURACY_print_bio(BIO *bio, const TS_ACCURACY *a)
{
    if (a->seconds != NULL)
        TS_ASN1_INTEGER_print_bio(bio, a->seconds);
    else
        BIO_printf(bio, "unspecified");
    BIO_printf(bio, " seconds, ");
    if (a->millis != NULL)
        TS_ASN1_INTEGER_print_bio(bio, a->millis);
    else
        BIO_printf(bio, "unspecified");
    BIO_printf(bio, " millis, ");
    if (a->micros != NULL)
        TS_ASN1_INTEGER_print_bio(bio, a->micros);
    else
        BIO_printf(bio, "unspecified");
    BIO_printf(bio, " micros");

    return 1;
}