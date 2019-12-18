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
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void send_http_get_and_print(BIO * sbio) { 
		int len;
		char tmpbuf[1024];
		BIO * out = BIO_new_fp(stdout, BIO_NOCLOSE);

		BIO_puts(sbio, "GET / HTTP/1.0\n\n");
		for(;;) {
			len = BIO_read(sbio, tmpbuf, 1024);
			if(len <= 0) break;
		BIO_write(out, tmpbuf, len);
		}
		BIO_free(out);
}