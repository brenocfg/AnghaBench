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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_TYPE_DGRAM_SCTP ; 
 scalar_t__ BIO_method_type (int /*<<< orphan*/ *) ; 

int BIO_dgram_is_sctp(BIO *bio)
{
    return (BIO_method_type(bio) == BIO_TYPE_DGRAM_SCTP);
}