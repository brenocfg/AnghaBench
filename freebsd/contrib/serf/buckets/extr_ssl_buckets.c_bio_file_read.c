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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_read (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/ * bio_get_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bio_file_read(BIO *bio, char *in, int inlen)
{
    apr_file_t *file = bio_get_data(bio);
    apr_status_t status;
    apr_size_t len;

    len = inlen;
    status = apr_file_read(file, in, &len);

    if (!SERF_BUCKET_READ_ERROR(status)) {
        /* Oh suck. */
        if (APR_STATUS_IS_EOF(status)) {
            return -1;
        } else {
            return len;
        }
    }

    return -1;
}