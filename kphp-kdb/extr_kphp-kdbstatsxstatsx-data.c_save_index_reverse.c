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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int save_index_reverse (void) {
  assert (0);
/*  if (verbosity >= 4) {
    fprintf (stderr, "No, saving index in reverse mode.\n");
  }
  long long *tmp_shifts = zzmalloc (sizeof (long long) * (tot_counter_instances + 1));
  int *tmp_cnt = zzmalloc (sizeof (int) * (tot_counter_instances + 1));
  int *tmp_cnt_ver = zzmalloc (sizeof (int) * (tot_counter_instances + 1));

  int i;
  char *newidxname = NULL;

  if (engine_snapshot_replica) {
    newidxname = get_new_snapshot_name (engine_snapshot_replica, log_cur_pos(), engine_snapshot_replica->replica_prefix);
  }

  if (!newidxname || newidxname[0] == '-') {
    fprintf (stderr, "cannot write index: cannot compute its name\n");
    exit (1);
  }

  if (log_cur_pos() == jump_log_pos) {
    fprintf (stderr, "skipping generation of new snapshot %s for position %lld: snapshot for this position already exists\n",
       newidxname, jump_log_pos);
    return 0;
  } 

  if (verbosity > 0) {
    fprintf (stderr, "creating index %s at log position %lld\n", newidxname, log_cur_pos());
  }

  newidx_fd = open (newidxname, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0660);

  if (newidx_fd < 0) {
    fprintf (stderr, "cannot create new index file %s: %m\n", newidxname);
    exit (1);
  }

  struct index_header_v1 header;
  memset (&header, 0, sizeof (struct index_header_v1));

  header.magic = STATSX_INDEX_MAGIC + custom_version_names;
  header.created_at = time (NULL);
  header.log_pos1 = log_cur_pos ();
  header.log_timestamp = log_read_until;
  relax_log_crc32 (0);
  header.log_pos1_crc32 = ~log_crc32_complement;

  int count = 0;

  if (verbosity >= 2) {
    fprintf (stderr, "preparing index header\n");
  }

  for(i = 0; i<COUNTERS_PRIME; i++) {
    if (!Counters[i]) { continue; }
    p[count++] = i;
  }

  if (verbosity >= 2) {
    fprintf (stderr, "sorting Counters\n");
  }
  qsort (p, count, sizeof(int), cmp_cnt);

  if (verbosity >= 2) {
    fprintf (stderr, "sorting Counters done\n");
  }

  assert (lseek (newidx_fd, sizeof (struct index_header), SEEK_SET) == sizeof (struct index_header));
  int p1 = 0;
  int total_elem = 0;
  long long shift = sizeof (struct index_header);
  while (p1 < count) {
    if (p1 == 0 || Counters[p[p1]]->counter_id != Counters[p[p1-1]]->counter_id) {
      struct counter *C = get_counter_old (Counters[p[p1]]->counter_id, 0, 0);
      while (C) {
        if (C->created_at < timestamp_to_index) {
          assert (total_elem <= tot_counter_instances);
          tmp_shifts[total_elem] = shift;
          tmp_cnt[total_elem] = C->counter_id;
          tmp_cnt_ver[total_elem] = C->created_at;
          //if (verbosity >= 2) {
          //  fprintf (stderr, "%d\t", C->created_at);
          //}
          total_elem++;
          shift += write_counter (C);
          if (verbosity >= 1 && (total_elem & ((1 << 17) - 1)) == 0) {
            fprintf (stderr, "written %d counters (%lld memory)\n", total_elem, shift);
          }
        }
        C = C->prev;
      }
    } 
    while (tot_counters_allocated >= MAX_COUNTERS_ALLOCATED && free_LRU()) {
    }
    p1++;
  }
  header.shifts_offset = shift;
  header.total_elements = total_elem;

  if (verbosity >= 2) {
    fprintf (stderr, "writing offsets\n");
  }
  
  tmp_shifts[total_elem++] = shift;
  writeout (tmp_shifts, total_elem * sizeof (long long));
  writeout (tmp_cnt, total_elem * sizeof (int));
  writeout (tmp_cnt_ver, total_elem * sizeof (int));

  flushout ();

  if (verbosity >= 3) {
    fprintf (stderr, "writing header\n");
  }


  assert (lseek (newidx_fd, 0, SEEK_SET) == 0);
  writeout (&header, sizeof (struct index_header) );;
  flushout ();

  assert (fsync (newidx_fd) >= 0);
  assert (close (newidx_fd) >= 0);

  if (verbosity >= 3) {
    fprintf (stderr, "writing index done\n");
  }

  if (rename_temporary_snapshot (newidxname)) {
    fprintf (stderr, "cannot rename new index file from %s: %m\n", newidxname);
    unlink (newidxname);
    exit (1);
  }

  print_snapshot_name (newidxname);*/

  return 0;
}