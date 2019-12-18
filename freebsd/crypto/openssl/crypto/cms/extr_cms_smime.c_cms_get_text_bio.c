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
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_s_null () ; 
 int /*<<< orphan*/  BIO_set_mem_eof_return (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int CMS_TEXT ; 

__attribute__((used)) static BIO *cms_get_text_bio(BIO *out, unsigned int flags)
{
    BIO *rbio;
    if (out == NULL)
        rbio = BIO_new(BIO_s_null());
    else if (flags & CMS_TEXT) {
        rbio = BIO_new(BIO_s_mem());
        BIO_set_mem_eof_return(rbio, 0);
    } else
        rbio = out;
    return rbio;
}