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
typedef  int /*<<< orphan*/  UserIndex ;

/* Variables and functions */
 int HEAP_SIZE ; 
 int Heap ; 
 int MAX_DATA ; 
 int MAX_PAIRS ; 
 int date_adj ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int heap_a ; 
 int max_Dc ; 
 int /*<<< orphan*/  max_Dc_user ; 
 int max_Pc ; 
 int /*<<< orphan*/  max_Pc_user ; 
 int max_Ps ; 
 int /*<<< orphan*/  max_Ps_user ; 
 int msgs_analyzed ; 
 int msgs_read ; 
 int /*<<< orphan*/  percent (int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int tot_Dc ; 
 int tot_Pc ; 
 int tot_Ps ; 
 int tot_bad_senders ; 
 int tot_known_senders ; 
 int tot_sender_hashes ; 
 int tot_users ; 
 int ui_bytes ; 

void output_stats (void) {
  fprintf (stderr, "%d messages read, %d analyzed belonging to %d users\n", 
	   msgs_read, msgs_analyzed, tot_users);
  fprintf (stderr, "date adjusted %d times\n", date_adj);
  fprintf (stderr, "username data bytes: %d used out of %ld (%d%%)\n",
	   ui_bytes, (long)sizeof(UserIndex), percent (ui_bytes, sizeof(UserIndex)));
  fprintf (stderr, "messages with unknown correspondents: %lld out of %lld (%d%%)\n",
	   tot_bad_senders, tot_bad_senders+tot_known_senders, 
	   percent (tot_bad_senders, tot_bad_senders+tot_known_senders));
  fprintf (stderr, "imported username hashes: %lld out of %lld (%d%%)\n",
	   tot_sender_hashes, tot_Pc, percent (tot_sender_hashes, tot_Pc));
  fprintf (stderr, "messages buffer memory bytes: total %ld, used %ld (%d%%)\n",
	   HEAP_SIZE, (long)(heap_a - Heap), percent (heap_a - Heap, HEAP_SIZE));
  fprintf (stderr, "pairs:\ttotal %lld, maximal usage %d of %ld (%d%%) for user %d\n",
	   tot_Pc, max_Pc, MAX_PAIRS, percent (max_Pc, MAX_PAIRS), max_Pc_user);
  fprintf (stderr, "hashes:\ttotal %lld, maximal usage %d of %ld (%d%%) for user %d\n",
	   tot_Ps, max_Ps, MAX_PAIRS, percent (max_Ps, MAX_PAIRS), max_Ps_user);
  fprintf (stderr, "data:\ttotal %lld, maximal usage %d of %ld (%d%%) for user %d\n",
	   tot_Dc, max_Dc, MAX_DATA, percent (max_Dc, MAX_DATA), max_Dc_user);
}