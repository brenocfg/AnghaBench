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
typedef  int /*<<< orphan*/  uv_write_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int CHUNKS_PER_WRITE ; 
 int CHUNK_SIZE ; 
 int bytes_sent_done ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* uv_strerror (int) ; 
 int /*<<< orphan*/  write_cb_called ; 

__attribute__((used)) static void write_cb(uv_write_t* req, int status) {
  ASSERT(req != NULL);

  if (status) {
    fprintf(stderr, "uv_write error: %s\n", uv_strerror(status));
    ASSERT(0);
  }

  bytes_sent_done += CHUNKS_PER_WRITE * CHUNK_SIZE;
  write_cb_called++;
}