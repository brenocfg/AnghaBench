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
struct sshbuf {int dummy; } ;
struct kex {int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  flags; int /*<<< orphan*/  peer; int /*<<< orphan*/  my; int /*<<< orphan*/  kex_type; int /*<<< orphan*/  hostkey_nid; int /*<<< orphan*/  hostkey_type; int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/  we_need; int /*<<< orphan*/  session_id_len; int /*<<< orphan*/  session_id; } ;

/* Variables and functions */
 int sshbuf_put_cstring (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshbuf_put_stringb (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_u32 (struct sshbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kex_to_blob(struct sshbuf *m, struct kex *kex)
{
	int r;

	if ((r = sshbuf_put_string(m, kex->session_id,
	    kex->session_id_len)) != 0 ||
	    (r = sshbuf_put_u32(m, kex->we_need)) != 0 ||
	    (r = sshbuf_put_cstring(m, kex->hostkey_alg)) != 0 ||
	    (r = sshbuf_put_u32(m, kex->hostkey_type)) != 0 ||
	    (r = sshbuf_put_u32(m, kex->hostkey_nid)) != 0 ||
	    (r = sshbuf_put_u32(m, kex->kex_type)) != 0 ||
	    (r = sshbuf_put_stringb(m, kex->my)) != 0 ||
	    (r = sshbuf_put_stringb(m, kex->peer)) != 0 ||
	    (r = sshbuf_put_u32(m, kex->flags)) != 0 ||
	    (r = sshbuf_put_cstring(m, kex->client_version_string)) != 0 ||
	    (r = sshbuf_put_cstring(m, kex->server_version_string)) != 0)
		return r;
	return 0;
}