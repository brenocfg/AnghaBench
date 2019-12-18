#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int shutdown; int init; int num; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_set_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BIO_set_shutdown (TYPE_1__*,int) ; 

__attribute__((used)) static int bio_bucket_create(BIO *bio)
{
#ifdef USE_OPENSSL_1_1_API
    BIO_set_shutdown(bio, 1);
    BIO_set_init(bio, 1);
    BIO_set_data(bio, NULL);
#else
    bio->shutdown = 1;
    bio->init = 1;
    bio->num = -1;
    bio->ptr = NULL;
#endif

    return 1;
}