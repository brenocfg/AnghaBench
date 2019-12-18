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
struct strbuf {int /*<<< orphan*/  len; } ;
struct signature_check {char result; void* gpg_status; void* gpg_output; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  parse_gpg_output (struct signature_check*) ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int verify_signed_buffer (char const*,size_t,char const*,size_t,struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  xmemdupz (char const*,size_t) ; 

int check_signature(const char *payload, size_t plen, const char *signature,
	size_t slen, struct signature_check *sigc)
{
	struct strbuf gpg_output = STRBUF_INIT;
	struct strbuf gpg_status = STRBUF_INIT;
	int status;

	sigc->result = 'N';

	status = verify_signed_buffer(payload, plen, signature, slen,
				      &gpg_output, &gpg_status);
	if (status && !gpg_output.len)
		goto out;
	sigc->payload = xmemdupz(payload, plen);
	sigc->gpg_output = strbuf_detach(&gpg_output, NULL);
	sigc->gpg_status = strbuf_detach(&gpg_status, NULL);
	parse_gpg_output(sigc);
	status |= sigc->result != 'G' && sigc->result != 'U';

 out:
	strbuf_release(&gpg_status);
	strbuf_release(&gpg_output);

	return !!status;
}