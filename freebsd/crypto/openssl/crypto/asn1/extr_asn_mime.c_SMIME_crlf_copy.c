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
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int MAX_SMLEN ; 
 int SMIME_ASCIICRLF ; 
 int SMIME_BINARY ; 
 int SMIME_TEXT ; 
 char strip_eol (char*,int*,int) ; 

int SMIME_crlf_copy(BIO *in, BIO *out, int flags)
{
    BIO *bf;
    char eol;
    int len;
    char linebuf[MAX_SMLEN];
    /*
     * Buffer output so we don't write one line at a time. This is useful
     * when streaming as we don't end up with one OCTET STRING per line.
     */
    bf = BIO_new(BIO_f_buffer());
    if (bf == NULL)
        return 0;
    out = BIO_push(bf, out);
    if (flags & SMIME_BINARY) {
        while ((len = BIO_read(in, linebuf, MAX_SMLEN)) > 0)
            BIO_write(out, linebuf, len);
    } else {
        int eolcnt = 0;
        if (flags & SMIME_TEXT)
            BIO_printf(out, "Content-Type: text/plain\r\n\r\n");
        while ((len = BIO_gets(in, linebuf, MAX_SMLEN)) > 0) {
            eol = strip_eol(linebuf, &len, flags);
            if (len) {
                /* Not EOF: write out all CRLF */
                if (flags & SMIME_ASCIICRLF) {
                    int i;
                    for (i = 0; i < eolcnt; i++)
                        BIO_write(out, "\r\n", 2);
                    eolcnt = 0;
                }
                BIO_write(out, linebuf, len);
                if (eol)
                    BIO_write(out, "\r\n", 2);
            } else if (flags & SMIME_ASCIICRLF)
                eolcnt++;
            else if (eol)
                BIO_write(out, "\r\n", 2);
        }
    }
    (void)BIO_flush(out);
    BIO_pop(out);
    BIO_free(bf);
    return 1;
}