#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* base; } ;
struct TYPE_5__ {TYPE_1__ buf; } ;
typedef  TYPE_2__ write_req_t ;
typedef  int /*<<< orphan*/  uv_write_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* uv_strerror (int) ; 

__attribute__((used)) static void after_write(uv_write_t* req, int status) {
  write_req_t* wr;

  if (status) {
    fprintf(stderr, "uv_write error: %s\n", uv_strerror(status));
    ASSERT(0);
  }

  wr = (write_req_t*) req;

  /* Free the read/write buffer and the request */
  free(wr->buf.base);
  free(wr);
}