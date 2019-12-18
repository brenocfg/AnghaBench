#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct metafile_header {int dummy; } ;
struct TYPE_7__ {int global_offset; int local_offset; int key_len; int nrecords; int metafile_size; int /*<<< orphan*/  crc32; } ;

/* Variables and functions */
 TYPE_1__* buffer_meta ; 
 int /*<<< orphan*/  buffer_meta_init () ; 
 TYPE_1__* buffer_meta_key ; 
 int buffer_meta_key_len ; 
 int buffer_meta_number ; 
 int buffer_meta_pos ; 
 TYPE_1__* buffer_shifts ; 
 unsigned int compute_crc32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  compute_crc32_combine (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int global_offset ; 
 TYPE_1__ metafile_header_tmp ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int write_buffer_number ; 
 int /*<<< orphan*/  writeout (TYPE_1__*,int) ; 

void buffer_meta_flush () {
  metafile_header_tmp.global_offset = global_offset;
  metafile_header_tmp.local_offset = sizeof (struct metafile_header) + buffer_meta_key_len;
  metafile_header_tmp.key_len = buffer_meta_key_len;
  metafile_header_tmp.nrecords = buffer_meta_number;
  metafile_header_tmp.metafile_size = buffer_meta_pos + buffer_meta_number * sizeof (long long);
  unsigned crc32_l = compute_crc32 (buffer_shifts, buffer_meta_number * sizeof (long long));
  unsigned crc32_r = compute_crc32 (buffer_meta, buffer_meta_pos);
  metafile_header_tmp.crc32 = compute_crc32_combine (crc32_l, crc32_r, buffer_meta_pos);
  writeout (&metafile_header_tmp, sizeof (struct metafile_header));
  writeout (buffer_meta_key, buffer_meta_key_len);
  writeout (buffer_shifts, buffer_meta_number * sizeof (long long));
  writeout (buffer_meta, buffer_meta_pos);
  if (verbosity >= 3) {
    fprintf (stderr, "writing metafile %d\n", write_buffer_number);
    fprintf (stderr, "offset = %lld\n", global_offset);
    fprintf (stderr, "number of records = %d\n", buffer_meta_number);
  }
  global_offset+=sizeof (struct metafile_header) + buffer_meta_key_len + buffer_meta_number * sizeof (long long) + buffer_meta_pos;
  buffer_meta_init();
}