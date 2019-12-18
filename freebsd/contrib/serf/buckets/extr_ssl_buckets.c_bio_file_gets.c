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
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_gets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bio_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int bio_file_gets(BIO *bio, char *in, int inlen)
{
    apr_file_t *file = bio_get_data(bio);
    apr_status_t status;

    status = apr_file_gets(in, inlen, file);

    if (! status) {
        return (int)strlen(in);
    } else if (APR_STATUS_IS_EOF(status)) {
        return 0;
    } else {
        return -1; /* Signal generic error */
    }
}