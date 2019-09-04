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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double,double,double,...) ; 
 scalar_t__ line_no ; 
 int /*<<< orphan*/  rd_bytes ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ total_base62_number_len ; 
 int /*<<< orphan*/  total_keys ; 
 scalar_t__ total_urls_hash_len ; 
 scalar_t__ total_urls_len ; 
 int /*<<< orphan*/  wr_bytes ; 

void output_stats (void) {
  fprintf (stderr,
      "read: %lld bytes, %d records read\n"
      "written: %lld bytes\n"
      "stored keys: %lld\n",
      rd_bytes, line_no, wr_bytes,
      total_keys
      );
  if (total_urls_len && line_no) {
    fprintf (stderr, "average url length: %.3lf\n"
         "average url hash length: %.3lf\n"
         "average id in base62 length: %.3lf\n",
         ((double) (total_urls_len)) / ((double) (line_no)),
         ((double) (total_urls_hash_len)) / ((double) (line_no)),
         ((double) (total_base62_number_len)) / ((double) (line_no))
         );    
  }
}