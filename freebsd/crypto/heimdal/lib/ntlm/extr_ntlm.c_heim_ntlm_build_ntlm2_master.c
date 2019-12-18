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
struct ntlm_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 int heim_ntlm_keyex_wrap (struct ntlm_buf*,struct ntlm_buf*,struct ntlm_buf*) ; 
 int heim_ntlm_v2_base_session (void*,size_t,struct ntlm_buf*,struct ntlm_buf*) ; 

int
heim_ntlm_build_ntlm2_master(void *key, size_t len,
			     struct ntlm_buf *blob,
			     struct ntlm_buf *session,
			     struct ntlm_buf *master)
{
    struct ntlm_buf sess;
    int ret;

    ret = heim_ntlm_v2_base_session(key, len, blob, &sess);
    if (ret)
	return ret;

    ret = heim_ntlm_keyex_wrap(&sess, session, master);
    heim_ntlm_free_buf(&sess);

    return ret;
}