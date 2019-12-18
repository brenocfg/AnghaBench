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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_write (int /*<<< orphan*/ *,char const*,int*) ; 
 int /*<<< orphan*/ * bio_get_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bio_file_write(BIO *bio, const char *in, int inl)
{
    apr_file_t *file = bio_get_data(bio);
    apr_size_t nbytes;

    BIO_clear_retry_flags(bio);

    nbytes = inl;
    apr_file_write(file, in, &nbytes);

    return nbytes;
}