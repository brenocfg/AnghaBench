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
struct lev_generic {int dummy; } ;
struct lev_crc32 {long long pos; int /*<<< orphan*/  crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlogname ; 
 int disable_crc32 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long long,int /*<<< orphan*/ ,long long,...) ; 
 int /*<<< orphan*/  log_crc32_complement ; 
 int log_cur_pos () ; 
 long long log_headers_size ; 
 long long log_start_pos ; 
 int /*<<< orphan*/  process_timestamp_event (struct lev_generic*) ; 
 int /*<<< orphan*/  relax_log_crc32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void process_crc_event (struct lev_generic *E, int offset) {
  relax_log_crc32 (0);
  if (!(disable_crc32 & 2)) {
    long long cur_pos = log_cur_pos() + offset;
    if (~log_crc32_complement != ((struct lev_crc32 *) E)->crc32) {
      fprintf (stderr, "crc mismatch at binlog position %lld, file %s offset %lld\n", cur_pos, binlogname, cur_pos - log_start_pos + log_headers_size);
      assert (~log_crc32_complement == ((struct lev_crc32 *) E)->crc32);
    }
    if (cur_pos != ((struct lev_crc32 *) E)->pos) {
      fprintf (stderr, "position at binlog position %lld, file %s offset %lld: expected position %lld\n", cur_pos, binlogname, cur_pos - log_start_pos + log_headers_size, ((struct lev_crc32 *) E)->pos);
      assert (cur_pos == ((struct lev_crc32 *) E)->pos);
    }
  }
  process_timestamp_event (E);
}