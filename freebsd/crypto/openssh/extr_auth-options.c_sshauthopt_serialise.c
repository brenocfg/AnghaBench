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
typedef  int /*<<< orphan*/  u_int ;
struct sshbuf {int dummy; } ;
struct sshauthopt {int permit_port_forwarding_flag; int permit_agent_forwarding_flag; int permit_x11_forwarding_flag; int permit_pty_flag; int permit_user_rc; int restricted; int cert_authority; int force_tun_device; char* cert_principals; char* force_command; char* required_from_host_cert; char* required_from_host_keys; int /*<<< orphan*/  npermitlisten; int /*<<< orphan*/  permitlisten; int /*<<< orphan*/  npermitopen; int /*<<< orphan*/  permitopen; int /*<<< orphan*/  nenv; int /*<<< orphan*/  env; int /*<<< orphan*/  valid_before; } ;

/* Variables and functions */
 int SSH_ERR_INTERNAL_ERROR ; 
 int serialise_array (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int serialise_nullable_string (struct sshbuf*,char*) ; 
 int sshbuf_put_u32 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_u64 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_u8 (struct sshbuf*,int) ; 

int
sshauthopt_serialise(const struct sshauthopt *opts, struct sshbuf *m,
    int untrusted)
{
	int r = SSH_ERR_INTERNAL_ERROR;

	/* Flag and simple integer options */
	if ((r = sshbuf_put_u8(m, opts->permit_port_forwarding_flag)) != 0 ||
	    (r = sshbuf_put_u8(m, opts->permit_agent_forwarding_flag)) != 0 ||
	    (r = sshbuf_put_u8(m, opts->permit_x11_forwarding_flag)) != 0 ||
	    (r = sshbuf_put_u8(m, opts->permit_pty_flag)) != 0 ||
	    (r = sshbuf_put_u8(m, opts->permit_user_rc)) != 0 ||
	    (r = sshbuf_put_u8(m, opts->restricted)) != 0 ||
	    (r = sshbuf_put_u8(m, opts->cert_authority)) != 0 ||
	    (r = sshbuf_put_u64(m, opts->valid_before)) != 0)
		return r;

	/* tunnel number can be negative to indicate "unset" */
	if ((r = sshbuf_put_u8(m, opts->force_tun_device == -1)) != 0 ||
	    (r = sshbuf_put_u32(m, (opts->force_tun_device < 0) ?
	    0 : (u_int)opts->force_tun_device)) != 0)
		return r;

	/* String options; these may be NULL */
	if ((r = serialise_nullable_string(m,
	    untrusted ? "yes" : opts->cert_principals)) != 0 ||
	    (r = serialise_nullable_string(m,
	    untrusted ? "true" : opts->force_command)) != 0 ||
	    (r = serialise_nullable_string(m,
	    untrusted ? NULL : opts->required_from_host_cert)) != 0 ||
	    (r = serialise_nullable_string(m,
	     untrusted ? NULL : opts->required_from_host_keys)) != 0)
		return r;

	/* Array options */
	if ((r = serialise_array(m, opts->env,
	    untrusted ? 0 : opts->nenv)) != 0 ||
	    (r = serialise_array(m, opts->permitopen,
	    untrusted ? 0 : opts->npermitopen)) != 0 ||
	    (r = serialise_array(m, opts->permitlisten,
	    untrusted ? 0 : opts->npermitlisten)) != 0)
		return r;

	/* success */
	return 0;
}