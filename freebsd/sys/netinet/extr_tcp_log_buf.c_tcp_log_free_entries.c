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
struct tcp_log_stailq {int dummy; } ;
struct tcp_log_mem {int dummy; } ;

/* Variables and functions */
 struct tcp_log_mem* STAILQ_FIRST (struct tcp_log_stailq*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct tcp_log_stailq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_log_entry_refcnt_rem (struct tcp_log_mem*) ; 
 int /*<<< orphan*/  tcp_log_free_log_common (struct tcp_log_mem*,int*) ; 
 int /*<<< orphan*/  tlm_queue ; 

__attribute__((used)) static void
tcp_log_free_entries(struct tcp_log_stailq *head, int *count)
{
	struct tcp_log_mem *log_entry;

	/* Free the entries. */
	while ((log_entry = STAILQ_FIRST(head)) != NULL) {
		STAILQ_REMOVE_HEAD(head, tlm_queue);
		tcp_log_entry_refcnt_rem(log_entry);
		tcp_log_free_log_common(log_entry, count);
	}
}