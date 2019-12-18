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
struct glxsb_session {int dummy; } ;
struct cryptop {int /*<<< orphan*/  crp_flags; int /*<<< orphan*/  crp_buf; } ;
struct cryptodesc {int crd_flags; int /*<<< orphan*/  crd_klen; int /*<<< orphan*/  crd_key; } ;

/* Variables and functions */
 int CRD_F_KEY_EXPLICIT ; 
 int glxsb_authcompute (struct glxsb_session*,struct cryptodesc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxsb_hash_key_setup (struct glxsb_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
glxsb_hash_process(struct glxsb_session *ses, struct cryptodesc *maccrd,
    struct cryptop *crp)
{
	int error;

	if ((maccrd->crd_flags & CRD_F_KEY_EXPLICIT) != 0)
		glxsb_hash_key_setup(ses, maccrd->crd_key, maccrd->crd_klen);

	error = glxsb_authcompute(ses, maccrd, crp->crp_buf, crp->crp_flags);
	return (error);
}