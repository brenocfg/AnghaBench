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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* uv_err_name (int) ; 
 char* uv_strerror (int) ; 

__attribute__((used)) static void after_write(uv_write_t* req, int status) {
  write_req_t* wr;

  /* Free the read/write buffer and the request */
  wr = (write_req_t*) req;
  free(wr->buf.base);
  free(wr);

  if (status == 0)
    return;

  fprintf(stderr,
          "uv_write error: %s - %s\n",
          uv_err_name(status),
          uv_strerror(status));
}