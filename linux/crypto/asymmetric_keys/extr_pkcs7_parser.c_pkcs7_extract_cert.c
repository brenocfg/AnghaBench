#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct x509_certificate {unsigned char index; struct x509_certificate* next; TYPE_1__* id; scalar_t__ subject; } ;
struct pkcs7_parse_context {unsigned char x509_index; struct x509_certificate** ppcerts; scalar_t__ data; } ;
struct TYPE_2__ {unsigned char len; scalar_t__ data; } ;

/* Variables and functions */
 int ASN1_CONS_BIT ; 
 int ASN1_SEQ ; 
 int ASN1_UNIV ; 
 int EBADMSG ; 
 scalar_t__ IS_ERR (struct x509_certificate*) ; 
 int PTR_ERR (struct x509_certificate*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char,scalar_t__) ; 
 struct x509_certificate* x509_cert_parse (void const*,size_t) ; 

int pkcs7_extract_cert(void *context, size_t hdrlen,
		       unsigned char tag,
		       const void *value, size_t vlen)
{
	struct pkcs7_parse_context *ctx = context;
	struct x509_certificate *x509;

	if (tag != ((ASN1_UNIV << 6) | ASN1_CONS_BIT | ASN1_SEQ)) {
		pr_debug("Cert began with tag %02x at %lu\n",
			 tag, (unsigned long)ctx - ctx->data);
		return -EBADMSG;
	}

	/* We have to correct for the header so that the X.509 parser can start
	 * from the beginning.  Note that since X.509 stipulates DER, there
	 * probably shouldn't be an EOC trailer - but it is in PKCS#7 (which
	 * stipulates BER).
	 */
	value -= hdrlen;
	vlen += hdrlen;

	if (((u8*)value)[1] == 0x80)
		vlen += 2; /* Indefinite length - there should be an EOC */

	x509 = x509_cert_parse(value, vlen);
	if (IS_ERR(x509))
		return PTR_ERR(x509);

	x509->index = ++ctx->x509_index;
	pr_debug("Got cert %u for %s\n", x509->index, x509->subject);
	pr_debug("- fingerprint %*phN\n", x509->id->len, x509->id->data);

	*ctx->ppcerts = x509;
	ctx->ppcerts = &x509->next;
	return 0;
}