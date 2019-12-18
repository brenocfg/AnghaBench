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
struct padlock_softc {int dummy; } ;
struct padlock_session {int /*<<< orphan*/  ses_fpu_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpu_kern_free_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padlock_hash_free (struct padlock_session*) ; 

__attribute__((used)) static void
padlock_freesession_one(struct padlock_softc *sc, struct padlock_session *ses)
{

	padlock_hash_free(ses);
	fpu_kern_free_ctx(ses->ses_fpu_ctx);
}