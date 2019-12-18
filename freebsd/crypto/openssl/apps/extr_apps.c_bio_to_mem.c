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
 int /*<<< orphan*/  BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 

int bio_to_mem(unsigned char **out, int maxlen, BIO *in)
{
    BIO *mem;
    int len, ret;
    unsigned char tbuf[1024];

    mem = BIO_new(BIO_s_mem());
    if (mem == NULL)
        return -1;
    for (;;) {
        if ((maxlen != -1) && maxlen < 1024)
            len = maxlen;
        else
            len = 1024;
        len = BIO_read(in, tbuf, len);
        if (len < 0) {
            BIO_free(mem);
            return -1;
        }
        if (len == 0)
            break;
        if (BIO_write(mem, tbuf, len) != len) {
            BIO_free(mem);
            return -1;
        }
        maxlen -= len;

        if (maxlen == 0)
            break;
    }
    ret = BIO_get_mem_data(mem, (char **)out);
    BIO_set_flags(mem, BIO_FLAGS_MEM_RDONLY);
    BIO_free(mem);
    return ret;
}