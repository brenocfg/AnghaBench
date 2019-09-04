#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_req_t ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ req_list_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 TYPE_1__* req_freelist ; 

__attribute__((used)) static uv_req_t* req_alloc(void) {
  req_list_t* req;

  req = req_freelist;
  if (req != NULL) {
    req_freelist = req->next;
    return (uv_req_t*) req;
  }

  req = (req_list_t*) malloc(sizeof *req);
  return (uv_req_t*) req;
}