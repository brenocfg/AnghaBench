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
typedef  int /*<<< orphan*/  OCSP_RESPONSE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 size_t BIO_ctrl_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 scalar_t__ MSG_DEBUG ; 
 int /*<<< orphan*/  OCSP_RESPONSE_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 scalar_t__ wpa_debug_level ; 
 int /*<<< orphan*/  wpa_printf (scalar_t__,char*,char*) ; 

__attribute__((used)) static void ocsp_debug_print_resp(OCSP_RESPONSE *rsp)
{
#ifndef CONFIG_NO_STDOUT_DEBUG
	BIO *out;
	size_t rlen;
	char *txt;
	int res;

	if (wpa_debug_level > MSG_DEBUG)
		return;

	out = BIO_new(BIO_s_mem());
	if (!out)
		return;

	OCSP_RESPONSE_print(out, rsp, 0);
	rlen = BIO_ctrl_pending(out);
	txt = os_malloc(rlen + 1);
	if (!txt) {
		BIO_free(out);
		return;
	}

	res = BIO_read(out, txt, rlen);
	if (res > 0) {
		txt[res] = '\0';
		wpa_printf(MSG_DEBUG, "OpenSSL: OCSP Response\n%s", txt);
	}
	os_free(txt);
	BIO_free(out);
#endif /* CONFIG_NO_STDOUT_DEBUG */
}