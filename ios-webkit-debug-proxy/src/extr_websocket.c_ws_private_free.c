#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_private_t ;
struct ws_private {int dummy; } ;
struct TYPE_5__ {struct TYPE_5__* req_host; struct TYPE_5__* sec_answer; struct TYPE_5__* sec_key; struct TYPE_5__* protocol; struct TYPE_5__* http_version; struct TYPE_5__* resource; struct TYPE_5__* method; int /*<<< orphan*/  data; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  cb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void ws_private_free(ws_private_t my) {
  if (my) {
    cb_free(my->in);
    cb_free(my->out);
    cb_free(my->data);
    free(my->method);
    free(my->resource);
    free(my->http_version);
    free(my->protocol);
    free(my->sec_key);
    free(my->sec_answer);
    free(my->req_host);
    memset(my, 0, sizeof(struct ws_private));
    free(my);
  }
}