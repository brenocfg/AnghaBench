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
struct TYPE_4__ {void* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_set_data (TYPE_1__*,void*) ; 

__attribute__((used)) static void bio_set_data(BIO *bio, void *data)
{
#ifdef USE_OPENSSL_1_1_API
    BIO_set_data(bio, data);
#else
    bio->ptr = data;
#endif
}