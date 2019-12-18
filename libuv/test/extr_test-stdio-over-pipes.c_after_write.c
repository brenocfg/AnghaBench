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
 int /*<<< orphan*/  after_write_cb_called ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* uv_strerror (int) ; 

__attribute__((used)) static void after_write(uv_write_t* req, int status) {
  if (status) {
    fprintf(stderr, "uv_write error: %s\n", uv_strerror(status));
    ASSERT(0);
  }

  /* Free the read/write buffer and the request */
  free(req);

  after_write_cb_called++;
}