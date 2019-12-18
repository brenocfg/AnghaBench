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
struct audit_pipe_entry {scalar_t__ ape_record_len; } ;
struct audit_pipe {scalar_t__ ap_qbyteslen; scalar_t__ ap_qlen; scalar_t__ ap_qoffset; int /*<<< orphan*/  ap_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_ASSERT (struct audit_pipe*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct audit_pipe_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct audit_pipe_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ape_queue ; 
 int /*<<< orphan*/  audit_pipe_entry_free (struct audit_pipe_entry*) ; 

__attribute__((used)) static void
audit_pipe_flush(struct audit_pipe *ap)
{
	struct audit_pipe_entry *ape;

	AUDIT_PIPE_LOCK_ASSERT(ap);

	while ((ape = TAILQ_FIRST(&ap->ap_queue)) != NULL) {
		TAILQ_REMOVE(&ap->ap_queue, ape, ape_queue);
		ap->ap_qbyteslen -= ape->ape_record_len;
		audit_pipe_entry_free(ape);
		ap->ap_qlen--;
	}
	ap->ap_qoffset = 0;

	KASSERT(ap->ap_qlen == 0, ("audit_pipe_free: ap_qbyteslen"));
	KASSERT(ap->ap_qbyteslen == 0, ("audit_pipe_flush: ap_qbyteslen"));
}