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
typedef  TYPE_1__* hx509_crypto ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  HX509_CRYPTO_PADDING_NONE 129 
#define  HX509_CRYPTO_PADDING_PKCS7 128 
 int /*<<< orphan*/  PADDING_FLAGS ; 
 int /*<<< orphan*/  PADDING_NONE ; 
 int /*<<< orphan*/  PADDING_PKCS7 ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 

void
hx509_crypto_set_padding(hx509_crypto crypto, int padding_type)
{
    switch (padding_type) {
    case HX509_CRYPTO_PADDING_PKCS7:
	crypto->flags &= ~PADDING_FLAGS;
	crypto->flags |= PADDING_PKCS7;
	break;
    case HX509_CRYPTO_PADDING_NONE:
	crypto->flags &= ~PADDING_FLAGS;
	crypto->flags |= PADDING_NONE;
	break;
    default:
	_hx509_abort("Invalid padding");
    }
}