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
typedef  int u_int ;
struct audit_pipe_entry {int ape_record_len; int /*<<< orphan*/ * ape_record; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct audit_pipe {scalar_t__ ap_qlen; scalar_t__ ap_qlimit; int ap_qbyteslen; int ap_flags; int /*<<< orphan*/  ap_cv; int /*<<< orphan*/  ap_sigio; TYPE_1__ ap_selinfo; int /*<<< orphan*/  ap_inserts; int /*<<< orphan*/  ap_queue; int /*<<< orphan*/  ap_drops; } ;

/* Variables and functions */
 int AUDIT_PIPE_ASYNC ; 
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_ASSERT (struct audit_pipe*) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_AUDIT_PIPE_ENTRY ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PSOCK ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct audit_pipe_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ape_queue ; 
 int /*<<< orphan*/  audit_pipe_drops ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct audit_pipe_entry*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audit_pipe_append(struct audit_pipe *ap, void *record, u_int record_len)
{
	struct audit_pipe_entry *ape;

	AUDIT_PIPE_LOCK_ASSERT(ap);

	if (ap->ap_qlen >= ap->ap_qlimit) {
		ap->ap_drops++;
		audit_pipe_drops++;
		return;
	}

	ape = malloc(sizeof(*ape), M_AUDIT_PIPE_ENTRY, M_NOWAIT | M_ZERO);
	if (ape == NULL) {
		ap->ap_drops++;
		audit_pipe_drops++;
		return;
	}

	ape->ape_record = malloc(record_len, M_AUDIT_PIPE_ENTRY, M_NOWAIT);
	if (ape->ape_record == NULL) {
		free(ape, M_AUDIT_PIPE_ENTRY);
		ap->ap_drops++;
		audit_pipe_drops++;
		return;
	}

	bcopy(record, ape->ape_record, record_len);
	ape->ape_record_len = record_len;

	TAILQ_INSERT_TAIL(&ap->ap_queue, ape, ape_queue);
	ap->ap_inserts++;
	ap->ap_qlen++;
	ap->ap_qbyteslen += ape->ape_record_len;
	selwakeuppri(&ap->ap_selinfo, PSOCK);
	KNOTE_LOCKED(&ap->ap_selinfo.si_note, 0);
	if (ap->ap_flags & AUDIT_PIPE_ASYNC)
		pgsigio(&ap->ap_sigio, SIGIO, 0);
	cv_broadcast(&ap->ap_cv);
}